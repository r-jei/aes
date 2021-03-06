#include "aes.h"

unsigned char Sbox[16][16] = {\
			      { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f,
				0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7,
				0xab, 0x76 } ,				\
			      { 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47,
				0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4,
				0x72, 0xc0 } ,				\
			      { 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7,
				0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8,
				0x31, 0x15 } ,				\
			      { 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05,
				0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27,
				0xb2, 0x75 } ,
			      { 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a,
				0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3,
				0x2f, 0x84 } ,
			      { 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1,
				0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c,
				0x58, 0xcf } ,
			      { 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33,
				0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c,
				0x9f, 0xa8 } ,
			      { 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38,
				0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff,
				0xf3, 0xd2 } ,
			      { 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44,
				0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d,
				0x19, 0x73 } ,
			      { 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90,
				0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e,
				0x0b, 0xdb } ,
			      { 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24,
				0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95,
				0xe4, 0x79 } ,
			      { 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e,
				0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a,
				0xae, 0x08 } ,
			      { 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4,
				0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd,
				0x8b, 0x8a } ,
			      { 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6,
				0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1,
				0x1d, 0x9e } ,
			      { 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e,
				0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55,
				0x28, 0xdf } ,
			      { 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42,
				0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54,
				0xbb, 0x16 }
};

unsigned char InvSbox[16][16] = {
				 { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5,
				   0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3,
				   0xd7, 0xfb } ,
				 { 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff,
				   0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde,
				   0xe9, 0xcb } ,
				 { 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23,
				   0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa,
				   0xc3, 0x4e } ,
				 { 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24,
				   0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b,
				   0xd1, 0x25 } ,
				 { 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98,
				   0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65,
				   0xb6, 0x92 } ,
				 { 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9,
				   0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d,
				   0x9d, 0x84 } ,
				 { 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3,
				   0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3,
				   0x45, 0x06 } ,
				 { 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f,
				   0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13,
				   0x8a, 0x6b } ,
				 { 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc,
				   0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4,
				   0xe6, 0x73 } ,
				 { 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35,
				   0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75,
				   0xdf, 0x6e } ,
				 { 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5,
				   0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18,
				   0xbe, 0x1b } ,
				 { 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79,
				   0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd,
				   0x5a, 0xf4 } ,
				 { 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7,
				   0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80,
				   0xec, 0x5f } ,
				 { 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a,
				   0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9,
				   0x9c, 0xef } ,
				 { 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5,
				   0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53,
				   0x99, 0x61 } ,
				 { 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6,
				   0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21,
				   0x0c, 0x7d }
};

static int inv = 0;

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
  // Find the leftmost set bit of b. Values 
  unsigned char left = 0x80;
  for(int i = 0; i < 8; i++){
    if( (left & b) == left)
      break;
    left = left>>1;
  }

  /* Break b into the sum of its constituent 8 bits and then distribute.
   a * ( b7 ^ b6 ^ ... ^ b0) = (a*b7) ^ (a*b6) ^ ... ^ (a*b0) 
   You need only store the terms with non-zero bits: a*0 = 0 (no effect) */
  unsigned char xt_arr[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  unsigned char prev_xt = a;
  int arr_end = 0;
  for(unsigned char i = 0x01; i <= left && i > 0; i=i<<1){
    if( (b & i)==i )
      xt_arr[arr_end++] = prev_xt;
    prev_xt = xtime(prev_xt);
  }

  // sum the terms
  // ab7 ^ ab6 ^ ... ^ ab0
  unsigned char result = 0x00;
  for(int i = 0; i < arr_end; i++){
    result ^= xt_arr[i];
  }
  return result;
}

word itow(uint32_t i)
{
  word new;
  memset(new.b,0,WLEN);
  new.b[0] = (i & 0xff000000)>>24;
  new.b[1] = (i & 0x00ff0000)>>16;
  new.b[2] = (i & 0x0000ff00)>>8;
  new.b[3] = i & 0xff;
  return new;
}

uint32_t wtoi(word w)
{
  uint32_t i = 0x00;
  for(int it = 0; it < WLEN; it++){
    i ^= w.b[it]<<(4*(6-(it*2)));
  }
  return i;
}

void prints(int round, char* type, word state[Nb])
{
  char* msg;
  int num;
  if(inv != 0){
    msg = "round[%2i].i%s    ";
    num = inv-round;
  } else {
    msg = "round[%2i].%s    ";
    num = round;
  }
  printf(msg,num,type);
  for(int i = 0; i < Nb; i++){
    printf("%08x",wtoi(state[i]));
  }
  printf("\n");
}

word set_w(word* w, unsigned char val[WLEN]){
  w->b[0] = val[0];
  w->b[1] = val[1];
  w->b[2] = val[2];
  w->b[3] = val[3];
  return *w;
}

word xor_w(word a, word b){
  word new;
  for(int i = 0; i < WLEN; i++){
    new.b[i] = a.b[i] ^ b.b[i];
  }
  return new;
}

// Substitutes each byte of a four-byte input word with values from the S-Box.
// See section 5.1.1
word sub_w(word w, unsigned char box[16][16])
{
  word new;
  memset(new.b,0,WLEN);
  unsigned char temp = 0x00;

  for(int i = 0; i < WLEN; i++){
    temp = w.b[i];
    int col = (uint32_t) (0x0f & temp);
    int row = (uint32_t) (0xf0 & temp)>>4;
    new.b[i] = box[row][col];
  }
  
  return new;
}

//take in [a0,a1,a2,a3], return [a1,a2,a3,a0]
word rot_w(word w)
{
  word new;
  new.b[0] = w.b[1];
  new.b[1] = w.b[2];
  new.b[2] = w.b[3];
  new.b[3] = w.b[0];
  return new;
}

word rcon(int num)
{
  word res;
  unsigned char c = 0x01;
  
  for(int i = 1; i < num; i++){
    c = xtime(c);
  }
  
  unsigned char bytes[WLEN] = {c, 0x00, 0x00, 0x00};
  set_w(&res, bytes);
  return res;
}


/*
 * @key: an array of Nk 32-bit words. 
 * @warr: The key schedule to be generated. Initial Nb words, and Nr rounds requiring Nb words of key data.
 * @Nk: Number of 32-bit words comprising the cipher key
 * todo: clean this up a bit!
 */
void key_exp(unsigned char key[],
		       uint32_t warr[],
		       int Nk)
{
  int Nr = Nk+6; // # of rounds
  int words = Nb*(Nr+1);
  word temp;
  word w[words];
  
  for(int i = 0; i < words; i++){
    memset(w[i].b,0,WLEN);
  }
  
  int i = 0;
  while(i < Nk){
    for(int j = 0; j < WLEN; j++){
      w[i].b[j] = key[4*i+j];
      warr[i] = wtoi(w[i]);
    }
    i++;
  }

  i = Nk;
  while( i < words ){
    temp = w[i-1];
    if(i%Nk == 0){
      word rc = rcon(i/Nk);
      temp = xor_w( sub_w(rot_w(temp),Sbox),rc );
    }else if( Nk > 6 && (i%Nk)==4 ){
      temp = sub_w(temp,Sbox);
    }
    word temp_xor = xor_w(w[i-Nk],temp);
    w[i] = temp_xor;
    
    warr[i] = wtoi( temp_xor );
    i++;
  }
}

void add_key(word state[Nb], uint32_t warr[], int round)
{
  int num;
  char* msg;
  if(inv != 0){
      msg = "round[%2i].i%s    ";
      num = inv-round;
  } else {
    msg = "round[%2i].%s    ";
    num = round;
  }

  word keyw;
  int c, r;
  printf(msg,num,"k_sch");

  for(c = 0; c < Nb; c++){
    keyw = itow(warr[c+round*Nb]);
    printf("%08x",warr[c+round*Nb]);
    for(r = 0; r < WLEN; r++){
      state[c].b[r] = state[c].b[r] ^ keyw.b[r];
    }
  }
  printf("\n");
}

void sub_bytes(word state[Nb])
{
  state[0] = sub_w(state[0], Sbox);
  state[1] = sub_w(state[1], Sbox);
  state[2] = sub_w(state[2], Sbox);
  state[3] = sub_w(state[3], Sbox);
}

void inv_sub_bytes(word state[Nb])
{
  state[0] = sub_w(state[0], InvSbox);
  state[1] = sub_w(state[1], InvSbox);
  state[2] = sub_w(state[2], InvSbox);
  state[3] = sub_w(state[3], InvSbox);
}

void shift_rows(word state[Nb])
{
  int r, c;
  unsigned char temp[Nb];
  memset(temp, 0x00, Nb);
  /* row 0 isn't shifted */
  for(r = 1; r < WLEN; r++){
    for(c = 0; c < Nb; c++)
      temp[c] = state[c].b[r];
    
    for(c = 0; c < Nb; c++){
      state[c].b[r] = temp[(c+r)%Nb];
    }
  }
}

void inv_shift_rows(word state[Nb])
{
  int r, c;
  unsigned char temp[Nb];
  memset(temp, 0x00, Nb);
  /* row 0 isn't shifted */
  for(r = 1; r < WLEN; r++){
    for(c = 0; c < Nb; c++)
      temp[c] = state[c].b[r];
    
    for(c = 0; c < Nb; c++){
      state[(c+r)%Nb].b[r] = temp[c];
    }
  }
}

void mix_cols(word state[Nb])
{
  int c;
  unsigned char s0c, s1c, s2c, s3c;
  for(c = 0; c < Nb; c++){
    s0c = state[c].b[0];
    s1c = state[c].b[1];
    s2c = state[c].b[2];
    s3c = state[c].b[3];

    state[c].b[0] = ffMultiply(0x02,s0c) ^ ffMultiply(0x03,s1c) ^ s2c ^ s3c;
    state[c].b[1] = s0c ^ ffMultiply(0x02,s1c) ^ ffMultiply(0x03,s2c) ^ s3c;
    state[c].b[2] = s0c ^ s1c ^ ffMultiply(0x02,s2c) ^ ffMultiply(0x03,s3c);
    state[c].b[3] = ffMultiply(0x03,s0c) ^ s1c ^ s2c ^ ffMultiply(0x02,s3c);
  }
}

void inv_mix_cols(word state[Nb])
{
  int c;
  unsigned char s0c, s1c, s2c, s3c;
  for(c = 0; c < Nb; c++){
    s0c = state[c].b[0];
    s1c = state[c].b[1];
    s2c = state[c].b[2];
    s3c = state[c].b[3];

    state[c].b[0] = ffMultiply(0x0e,s0c) ^ ffMultiply(0x0b,s1c)
      ^ ffMultiply(0x0d,s2c) ^ ffMultiply(0x09,s3c);
    state[c].b[1] = ffMultiply(0x09,s0c) ^ ffMultiply(0x0e,s1c)
      ^ ffMultiply(0x0b,s2c) ^ ffMultiply(0x0d,s3c);
    state[c].b[2] = ffMultiply(0x0d,s0c) ^ ffMultiply(0x09,s1c)
      ^ ffMultiply(0x0e,s2c) ^ ffMultiply(0x0b,s3c);
    state[c].b[3] = ffMultiply(0x0b,s0c) ^ ffMultiply(0x0d,s1c)
      ^ ffMultiply(0x09,s2c) ^ ffMultiply(0x0e,s3c);
  }
}

void load_state(unsigned char in[4*Nb], word state[Nb])
{
  int r, c;
  for(c = 0; c < Nb; c++){
    for(r = 0; r < WLEN; r++){
      state[c].b[r] = in[r+4*c];
    }
  }
}

void unload_state(unsigned char out[4*Nb], word state[Nb])
{
  int r, c;
  for(c = 0; c < 4; c++){
    for(r = 0; r < Nb; r++){
      out[r+4*c] = state[c].b[r];
    }
  }
}

void cipher(unsigned char in[4*Nb], unsigned char out[4*Nb], uint32_t w[], int Nk, int verbose)
{
  printf("CIPHER (ENCRYPT):\n");
  int Nr = Nk+6;
  word state[Nb];
  load_state(in, state);
  
  int round = 0;
  inv = 0;
  prints(round,"input",state);
  add_key(state, w, round); //see sec. 5.1.4
  
  for(round = 1; round < Nr; round++){
    prints(round,"start",state);
    sub_bytes(state); //see sec. 5.1.1
    prints(round,"s_box",state);
    shift_rows(state); //see sec. 5.1.2
    prints(round,"s_row",state);
    mix_cols(state); //see sec. 5.1.3
    prints(round,"m_col",state);
    add_key(state, w, round);
  }

  prints(round,"start",state);
  sub_bytes(state);
  prints(round,"s_box",state);
  shift_rows(state);
  prints(round,"s_row",state);
  add_key(state, w, round);
  prints(round,"output",state);
  printf("\n");

  unload_state(out,state);
}

void inv_cipher(unsigned char in[4*Nb], unsigned char out[4*Nb], uint32_t w[], int Nk, int verbose)
{
  printf("INVERSE CIPHER (DECRYPT):\n");
  int Nr = Nk+6;
  word state[Nb];
  load_state(in, state);

  int round = Nr;
  inv = Nr;
  prints(round,"input",state);
  add_key(state, w, round);
  
  for(round = Nr-1; round >= 1; round--){
    prints(round,"start",state);
    inv_shift_rows(state);
    prints(round,"s_row",state);
    inv_sub_bytes(state);
    prints(round,"s_box",state);
    add_key(state,w,round);
    prints(round,"k_add",state);
    inv_mix_cols(state);
  }

  prints(round,"start",state);
  inv_shift_rows(state);
  prints(round,"s_row",state);
  inv_sub_bytes(state);
  prints(round,"s_box",state);
  add_key(state,w,round);
  prints(round,"output",state);
  printf("\n");
  
  unload_state(out,state);
}
