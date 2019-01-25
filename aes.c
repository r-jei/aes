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
  //find the rightmost bit of b
  unsigned char right = 0x80;
  for(int i = 0; i < 8; i++){
    if( (right & b) == right)
      break;
    right = right>>1;
  }

  // a * ( b7 ^ b6 ^ ... ^ b0) = (a*b7) ^ (a*b6) ^ ... ^ (a*b0)
  // calculate (a*b7), ... (a*b0). If the nth bit is not set, there is no need
  // to store its multiply, because (a*0) = 0
  unsigned char xt_arr[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  unsigned char prev_xt = a;
  int arr_end = 0;
  for(unsigned char i = 0x01; i <= right; i=i<<1){
    if( (b & i)==i )
      xt_arr[arr_end++] = prev_xt;
    prev_xt = xtime(prev_xt);
  }

  // ab7 ^ ab6 ^ ... ^ ab0
  unsigned char result = 0x00;
  for(int i = 0; i < arr_end; i++){
    result ^= xt_arr[i];
  }
  return result;
}
