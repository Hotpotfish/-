#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h> /* everything... */
#include <linux/cdev.h>
#include <asm/uaccess.h> /* copy_*_user */
#include <linux/semaphore.h>
//#include <linux/delay.h>
#include <linux/wait.h>
//#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/sched.h>

struct semaphore mutex;
MODULE_LICENSE("GPL");
int scull_major = 0;
int scull_minor = 0;
struct cdev cdev; /* Char device structure */
#define MAX_SIZE 10
size_t begin = 0;
size_t end = 0;
char store[MAX_SIZE];

wait_queue_head_t inq;

wait_queue_head_t outq;

int outp = 0;
int size = 0;

/*
* Open and close
*/
int scull_open(struct inode *inode , struct file *filp){
  return 0; /* success */
}
int scull_release(struct inode *inode , struct file *filp){
  return 0;
}
/*
* Data management: read and write
*/
ssize_t scull_read(struct file *filp , char __user *buf, size_t count ,loff_t *f_pos){
	if (down_interruptible(&mutex))
return -ERESTARTSYS;
ssize_t retval = 0;
while (size == 0) {
up(&mutex);
if (wait_event_interruptible(inq, (size != 0)))
return -ERESTARTSYS; /* signal: tell the fs layer to
handle it */
if (down_interruptible(&mutex))
return -ERESTARTSYS;
}
if (count > size)
count = size;
if (outp + count > MAX_SIZE)
count = MAX_SIZE - outp;
if (copy_to_user(buf, store + outp, count)) {
retval = -EFAULT;
goto out;
}
outp += count;
if (outp == MAX_SIZE)
outp = 0;
retval = count;
size -= count;
out:
up(&mutex);
wake_up_interruptible(&outq);
return retval;
}

ssize_t scull_write(struct file *filp , const char __user *buf,size_t count ,loff_t *f_pos) {
	if (down_interruptible(&mutex))
		return -ERESTARTSYS;
	ssize_t retval = 0;
	while (size == 10)	{
		up(&mutex);
		if (wait_event_interruptible(outq, (size != 10)))
			return -ERESTARTSYS;
		if (down_interruptible(&mutex))
			return -ERESTARTSYS;
	}
	if (count > MAX_SIZE - size )
		count = MAX_SIZE - size;
	if (outp + size + count > MAX_SIZE)
		count = MAX_SIZE - outp - size;
	if (copy_from_user(store + outp + size,buf, count)){
		retval = -EFAULT;
		goto out;
	}

	retval = count;
	size += count;
out:
	up(&mutex);
	wake_up_interruptible(&inq);

	return retval;
}

struct file_operations scull_fops = {
  .owner = THIS_MODULE ,
  .read = scull_read ,
  .write = scull_write ,
  .open = scull_open ,
  .release = scull_release ,
};
int scull_init_module(void) {

  sema_init(&mutex, 1);//≥ı ºªØ
init_waitqueue_head(&inq);
init_waitqueue_head(&outq);
  int result;
  dev_t dev = 0;
  /*
  * Get a range of minor numbers to work with , asking for a
  dynamic major
  */
  result = alloc_chrdev_region(&dev, scull_minor , 1, "scull");
  scull_major = MAJOR(dev);
  if (result < 0) {
    printk(KERN_WARNING "scull:?can't?get?major?%d\n",
           scull_major);
    return result;
  }
  /* register our device */
  cdev_init(&cdev , &scull_fops);
  cdev.owner = THIS_MODULE;
  cdev.ops = &scull_fops;
  result = cdev_add (&cdev , dev, 1);
  if (result) {
    printk(KERN_WARNING "Error?%d?adding?scull", result)
    ;
    unregister_chrdev_region(dev, 1);
    return result;
  }
  return 0; /* succeed */
}
void scull_cleanup_module(void) {
  /* cleanup_module is never called if registering failed */
  dev_t dev;
  cdev_del(&cdev);
  dev = MKDEV(scull_major , scull_minor);
  unregister_chrdev_region(dev, 1);
}
module_init(scull_init_module);
module_exit(scull_cleanup_module);


