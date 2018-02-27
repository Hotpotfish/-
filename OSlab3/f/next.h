
unsigned char mm[65536];


int step;
int next;
int end;
int BinToInt(unsigned char *s);


void IntToBin(int s, unsigned char *t);


int mm_init();


int mm_request(int n);


void mm_release(int p);
