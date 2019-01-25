#include "aes.h"
#include <stdio.h>

//returns 1 if successful, otherwise 0
int ffAdd_test()
{
  return ffAdd(0x57,0x83) == 0xd4;
}

int xtime_test()
{
  //TODO
  return -1;
}

int main(int argc, char** argv)
{
  printf("ffAdd_test: %d\n", ffAdd_test());
  return 0;
}
