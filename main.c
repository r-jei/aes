#include "aes.h"
#include <stdio.h>

int main(int argc, char** argv)
{
  printf("Hello, world!\n");
  printf("ffAdd_test: %x\n",ffAdd(0x57,0x83) == 0xd4);
  
  return 0;
}
