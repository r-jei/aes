#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define WLEN 4 // bytes in a word. Also the # of rows in the state
#define Nb 4 // no. of columns in the state. Nb=4 for this standard

typedef struct word { unsigned char b[WLEN]; } word;

unsigned char ffAdd(unsigned char a, unsigned char b);
unsigned char xtime(unsigned char a);
unsigned char ffMultiply(unsigned char a, unsigned char b);
word itow(uint32_t i);
uint32_t wtoi(word w);
word set_w(word* w, unsigned char val[WLEN]);
word xor_w(word a, word b);
word sub_w(word w);
word rot_w(word w);
word rcon(int i);
void key_exp(unsigned char key[], uint32_t warr[], int Nk);
void add_key(word state[Nb], uint32_t warr[], int round);
void sub_bytes(word state[Nb]);
void shift_rows(word state[Nb]);
void mix_cols(word state[Nb]);
void cipher(unsigned char in[4*Nb], unsigned char out[4*Nb], uint32_t w[], int nr);
