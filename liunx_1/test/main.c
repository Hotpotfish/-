#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>		/* everything... */
#include <linux/cdev.h>
#include <asm/uaccess.h>	/* copy_*_user */


int blackhole_major =   0;
int blackhole_minor =   0;
struct cdev cdev;	/* Char device structure */

#define MAX_SIZE    10
size_t size     =   0;
char store[MAX_SIZE];

/*
 * Open and close
 */

int blackhole_open(struct inode *inode, struct file *filp)
{
	/* trim to 0 the length of the device if open was write-only */
	if ( (filp->f_flags & O_ACCMODE) == O_WRONLY) {
		size = 0;
	}
	return 0;          /* success */
}

int blackhole_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/*
 * Data management: read and write
 */

ssize_t blackhole_read(struct file *filp, char __user *buf, size_t count,
                loff_t *f_pos)
{
    return 0;
}

ssize_t blackhole_write(struct file *filp, const char __user *buf, size_t count,
                loff_t *f_pos)
{
	ssize_t retval = -ENOMEM; /* value used in "goto out" statements */

	if (*f_pos >= MAX_SIZE)
		goto out;
	if (*f_pos + count > MAX_SIZE)
		count = MAX_SIZE - *f_pos;
	if (copy_from_user(store + *f_pos + size, buf, count)) {
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;

        /* update the size */
//	if (size < *f_pos)
	size = *f_pos;

  out:
	return retval;
}

loff_t blackhole_llseek(struct file *filp, loff_t off, int whence)
{
	loff_t newpos;

	switch(whence) {
	  case 0: /* SEEK_SET */
		newpos = off;
		break;

	  case 1: /* SEEK_CUR */
		newpos = filp->f_pos + off;
		break;

	  case 2: /* SEEK_END */
		newpos = size + off;
		break;

	  default: /* can't happen */
		return -EINVAL;
	}
	if (newpos < 0) return -EINVAL;
	filp->f_pos = newpos;
	return newpos;
}

struct file_operations blackhole_fops = {
	.owner =    THIS_MODULE,
	.llseek =   blackhole_llseek,
	.read =     blackhole_read,
	.write =    blackhole_write,
	.open =     blackhole_open,
	.release =  blackhole_release,
};


int blackhole_init_module(void)
{
	int result;
	dev_t dev = 0;

	/*
	 * Get a range of minor numbers to work with, asking for a dynamic major
	 */
	result = alloc_chrdev_region(&dev, blackhole_minor, 1, "blackhole");
	blackhole_major = MAJOR(dev);
	if (result < 0) {
		printk(KERN_WARNING "blackhole: can't get major %d\n", blackhole_major);
		return result;
	}


	/* register our device */
	cdev_init(&cdev, &blackhole_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &blackhole_fops;
	result = cdev_add (&cdev, dev, 1);
	if (result) {
		printk(KERN_WARNING "Error %d adding blackhole", result);
		unregister_chrdev_region(dev, 1);
		return result;
	}

	return 0; /* succeed */
}

void blackhole_cleanup_module(void)
{
	/* cleanup_module is never called if registering failed */
	dev_t dev;

	cdev_del(&cdev);

	dev = MKDEV(blackhole_major, blackhole_minor);
	unregister_chrdev_region(dev, 1);
}

module_init(blackhole_init_module);
module_exit(blackhole_cleanup_module);
