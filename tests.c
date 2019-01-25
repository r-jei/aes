#include "aes.h"
#include <stdio.h>
#include <string.h>

/*
 * Tests return 1 if successful, otherwise 0.
 * if vflag evaluates as true, the test is verbose.
 */

int ffAdd_test(int vflag)
{
  unsigned char ret = ffAdd(0x57,0x83);
  if(vflag)
    printf("ffAdd_test: ffAdd(0x57,0x83)=%x\n", ret);
  return ret == 0xd4;
}


int xtime_test(int vflag)
{
  unsigned char xt1 = xtime(0x57); // expect 0xae
  unsigned char xt2 = xtime(0xae); // expect 0x47
  unsigned char xt3 = xtime(0x47); // expect 0x83
  unsigned char xt4 = xtime(0x8e); // expect 0x07

  int tst1 = xt1 == 0xae;
  int tst2 = xt2 == 0x47;
  int tst3 = xt3 == 0x8e;
  int tst4 = xt4 == 0x07;
  
  if(vflag)
    printf("%x %x %x %x\n", xt1, xt2, xt3, xt4);
  return tst1 && tst2 && tst3 && tst4;
}

int ffMultiply_test(int vflag)
{
  unsigned char res = ffMultiply(0x57,0x13);
  if(vflag)
    printf("ffMultiply_test: ffMultiply(0x57,0x13)=%x\n", res);
  return res == 0xfe;
}

int main(int argc, char** argv)
{
  int vflag;
  if(argc > 1)
    vflag = strcmp(argv[1],"v")==0;
  printf("ffAdd_test: %d\n-------\n", ffAdd_test(vflag));
  printf("xtime_test: %d\n-------\n", xtime_test(vflag));
  printf("ffMultiply_test: %d\n-------\n", ffMultiply_test(vflag));
  return 0;
}
