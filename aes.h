#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define WLEN 4
#define Nb 4

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
void key_exp(unsigned char key[],uint32_t w_int[],int Nk);

