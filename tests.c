#include "aes.h"
#include <stdio.h>
#include <string.h>

#define TARLEN 9

uint32_t expanded[44] = { 0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c,
			  0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605,
			  0xf2c295f2, 0x7a96b943, 0x5935807a, 0x7359f67f,
			  0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b,
			  0xef44a541, 0xa8525b7f, 0xb671253b, 0xdb0bad00,
			  0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc,
			  0x6d88a37a, 0x110b3efd, 0xdbf98641, 0xca0093fd,
			  0x4e54f70e, 0x5f5fc9f3, 0x84a64fb2, 0x4ea6dc4f,
			  0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f,
			  0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e,
			  0xd014f9a8, 0xc9ee2589, 0xe13f0cc8, 0xb6630ca6 };

unsigned char in_ref[16]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			  0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };


/*
 * Tests return 1 if successful, otherwise 0.
 * if vflag evaluates as true, the test is verbose.
 * TODO use an actual unit testing framework.
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
  unsigned char ff1 = ffMultiply(0x57,0x13);
  unsigned char ff2 = ffMultiply(0x57,0x10);
  unsigned char ff3 = ffMultiply(0x57,0x02);
  unsigned char ff4 = ffMultiply(0x57,0x01);
  unsigned char ff5 = ffMultiply(0x57,0x00);
  unsigned char ff6 = ffMultiply(0x2,0xff);
  unsigned char ff7 = ffMultiply(0xff,0x02);
  unsigned char ff8 = ffMultiply(0x12,0x03);
  unsigned char ff9 = ffMultiply(0x03,0xff);

  if(vflag){
    printf("ffMultiply_test:\n 0x57,0x13=%x\n", ff1);
    printf("0x57,0x10=%x\n", ff2);
    printf("0x57,0x02=%x\n", ff3);
    printf("0x57,0x01=%x\n", ff4);
    printf("0x57,0x00=%x\n", ff5);
    printf("0x02,0xff=%x\n", ff6);
    printf("0xff,0x02=%x\n", ff7);
    printf("0x12,0x03=%x\n", ff8);
    printf("0x03,0xff=%x\n", ff9);
  }

  int t1 = ff1 == 0xfe;
  int t2 = ff2 == 0x07;
  int t3 = ff3 == 0xae;
  int t4 = ff4 == 0x57;
  int t5 = ff5 == 0x00;
  int t6 = ff6 == 0xe5;
  int t7 = ff7 == 0xe5;
  int t8 = ff8 == 0x36;
  int t9 = ff9 == 0x1a;
  
  int tarr[TARLEN] = {t1, t2, t3, t4, t5, t6, t7, t8, t9};
  for(int i = 0; i < TARLEN; i++){
    if(!tarr[i])
      return 0;
  }
  return 1;
}

int itow_test(int vflag)
{
  int val = 0x12345678;
  word w = itow(val);
  if(w.b[0]==0x12 && w.b[1]==0x34 && w.b[2]==0x56 && w.b[3]==0x78)
    return 1;
  else
    return 0;
}

int wtoi_test(int vflag)
{
  word w;
  w.b[0] = 0x12;
  w.b[1] = 0x34;
  w.b[2] = 0x56;
  w.b[3] = 0x78;
  uint32_t i = wtoi(w);
  if( i == 0x12345678 )
    return 1;
  else
    return 0;
}

int sw_test(int vflag)
{
  word w;
  word new;
  
  memset(w.b,0,4);
  uint32_t i1 = 0x00ff0ff0;
  
  new = sub_w(itow(i1),Sbox);
  if(vflag){
    printf("sw before: %x\n", i1);
    printf("sw after: %x\n", wtoi(new));
  }

  if( new.b[0]==Sbox[0][0] &&
      new.b[1]==Sbox[15][15] &&
      new.b[2]==Sbox[0][15] &&
      new.b[3]==Sbox[15][0] ){
    return 1;
  }else{
    return 0;
  }
}

int key_exp_test(int vflag)
{
  uint8_t key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
		      0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
  uint32_t w[44];
  key_exp(key,w,4);
  for(int i = 0; i < 44; i++){
    if( w[i] != expanded[i] )
      return 0;
  }
  return 1;
}

int rot_w_test(int vflag)
{
  word t1 = rot_w(itow(0x09cf4f3c));
  word t2 = rot_w(itow(0x2a6c7605));
  if( wtoi(t1) != 0xcf4f3c09 )
    return 0;
  if( wtoi(t2) != 0x6c76052a )
    return 0;
  return 1;
}

int compare(word state[Nb], uint32_t ref[])
{
  for(int i = 0; i < Nb; i++){
    if(wtoi(state[i]) != ref[i])
      return 0;
  }
  return 1;
}

void cipher_test(int vflag)
{
  uint32_t sub[4] =    { 0xd42711ae,
			 0xe0bf98f1,
			 0xb8b45de5,
			 0x1e415230 };

  uint32_t shift[4] =  { 0xd4bf5d30,
			 0xe0b452ae,
			 0xb84111f1,
			 0x1e2798e5 };

  uint32_t mix[4] =    { 0x046681e5,
			 0xe0cb199a,
			 0x48f8d37a,
			 0x2806264c };

  uint32_t rnd[4] =   { 0xa49c7ff2,
			0x689f352b,
			0x6b5bea43,
			0x026a5049 };
  word state[Nb];

  /* initialize state */
  state[0] = itow(0x193de3be);
  state[1] = itow(0xa0f4e22b);
  state[2] = itow(0x9ac68d2a);
  state[3] = itow(0xe9f84808);

  sub_bytes(state);
  printf("sub_bytes_test: %d\n-------\n", compare(state,sub));

  shift_rows(state);
  printf("shift_rows_test: %d\n-------\n", compare(state,shift));

  mix_cols(state);
  printf("mix_cols_test: %d\n-------\n", compare(state,mix));

  add_key(state, expanded, 1);
  printf("add_key_test: %d\n-------\n", compare(state,rnd));
  
}

int cipher128_test(int vflag)
{
  const int Nk = 4;
  const int Nr = Nk+6;
  unsigned char in[16]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

  unsigned char out[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  /* the correct reference for comparison */
  unsigned char result[16] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
			       0xd8,0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

  unsigned char key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  printf("PLAINTEXT: ");
  for(int i = 0; i < 16; i++)
    printf("%02x",in[i]);
  printf("\nKEY: ");
  for(int i = 0; i < 16; i++)
    printf("%02x",key[i]);
  printf("\n\n");


  uint32_t warr[Nb*(Nr+1)];
  
  key_exp(key, warr, Nk);
  cipher(in,out,warr,Nk,1);
  inv_cipher(out,in,warr,Nk,1);
  
  for(int i = 0; i < 16; i++){
    if((out[i] != result[i]) || (in[i] != in_ref[i]))
      return 0;
  }
  return 1;
}

int cipher192_test(int vflag)
{
  const int Nk = 6;
  const int Nr = Nk+6;
  unsigned char in[16]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
			    
  unsigned char out[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  /* the correct reference for comparison */
  unsigned char result[16] = { 0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0,
			       0x6e, 0xaf, 0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91
  };
  
  unsigned char key[24] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
			    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
    printf("PLAINTEXT: ");
  for(int i = 0; i < 16; i++)
    printf("%02x",in[i]);
  printf("\nKEY: ");
  for(int i = 0; i < 16; i++)
    printf("%02x",key[i]);
  printf("\n\n");

  uint32_t warr[Nb*(Nr+1)];
  
  key_exp(key, warr, Nk);
  cipher(in,out,warr,Nk,1);
  inv_cipher(out,in,warr,Nk,1);
  
  for(int i = 0; i < 16; i++){
    if((out[i] != result[i]) || (in[i] != in_ref[i]))
      return 0;
  }
  return 1;
}

int cipher256_test(int vflag)
{
  const int Nk = 8;
  const int Nr = Nk+6;
  unsigned char in[16]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
			    
  unsigned char out[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  /* the correct reference for comparison */
  unsigned char result[16] = { 0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf,
			      0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89};

  unsigned char key[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
			    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
			    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
  printf("PLAINTEXT: ");
  for(int i = 0; i < 16; i++)
    printf("%02x",in[i]);
  printf("\nKEY: ");
  for(int i = 0; i < 16; i++)
    printf("%02x",key[i]);
  printf("\n\n");
  
  uint32_t warr[Nb*(Nr+1)];
  key_exp(key, warr, Nk);
  
  cipher(in,out,warr,Nk,1);
  inv_cipher(out,in,warr,Nk,1);

  for(int i = 0; i < 16; i++){
    if((out[i] != result[i]) || (in[i] != in_ref[i]))
      return 0;
  }
  return 1;
}

int main(int argc, char** argv)
{
  int vflag;
  if(argc > 1)
    vflag = strcmp(argv[1],"-v")==0;

  printf(AES128_MSG);
  cipher128_test(vflag);
  printf(AES192_MSG);
  cipher192_test(vflag);
  printf(AES256_MSG);
  cipher256_test(vflag);
  
  return 0;
}
