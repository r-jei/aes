#include <stdio.h>
#include <string.h>

#define WLEN 4
#define Nb 4

typedef struct word { unsigned char b[WLEN]; } word;

unsigned char ffAdd(unsigned char a, unsigned char b);
unsigned char xtime(unsigned char a);
unsigned char ffMultiply(unsigned char a, unsigned char b);
word set_w(word* w, unsigned char val[WLEN]);
word xor_w(word a, word b);
word sub_w(word w);
word rot_w(word w);
word rcon(int i);
unsigned char* key_exp(unsigned char key[],word w[],int Nk);

