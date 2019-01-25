#include "aes.h"
#include <stdio.h>

//finite field addition; see FIPS 197, 4.1
unsigned char ffAdd(unsigned char a, unsigned char b)
{
  return a^b;
}

//finite field multiply by 2; see FIPS 197, 4.2.1
unsigned char xtime(unsigned char a)
{
  if( (0x80 & a)==0x80 )
    return (a<<1)^0x1b;
  return a<<1;
}

//finite field multiply using xtime; see FIPS 197, 4.2
unsigned char ffMultiply(unsigned char a, unsigned char b)
{
  
}
