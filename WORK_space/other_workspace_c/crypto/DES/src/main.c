/* Sofware DES functions
 * written 12 Dec 1986 by Phil Karn, KA9Q; large sections adapted from
 * the 1977 public-domain program by Jim Gillogly
 */
/* Those lines marked by [%] are added by iceman@zju.edu.cn
   for more readability.
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned char byte;

void des_init(void);
void des_set_key(byte *key);
void des_encrypt(byte *block);
void des_decrypt(byte *block);
void sbox_output_perm_table_init(void);
void perm_init(byte perm[8][256][8], byte p[64]);
void permute(byte *inblock, byte perm[8][256][8], byte *outblock);
void round(int num, byte block[8]);
void reverse_round(int num, byte block[8]);
void f(byte bufin[4], byte subkey[8], byte bufout[4]);

/* Tables defined in the Data Encryption Standard documents */

/* initial permutation IP
   ip的下标i是以0为基数的目标位的编号
   ip[i]是1为基数的源位的编号
   例如ip[0]=58表示源位第57位(base 0)变成目标位第0位
   ip[1]=50表示源位第49位(base 0)变成目标位第1位 
*/
byte ip[64] = 
{
   58, 50, 42, 34, 26, 18, 10,  2,
   60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6,
   64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1,
   59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5,
   63, 55, 47, 39, 31, 23, 15,  7
};

/* final permutation IP^-1 
   此表是ip的逆
   fp的下标i是源位号(base 0)
   fp[i]是目标位号(base 1)
   例如: fp[57]=1表示源位第57位(base 0)变成目标位第0位
*/
byte fp[64] = 
{
   40,  8, 48, 16, 56, 24, 64, 32,
   39,  7, 47, 15, 55, 23, 63, 31,
   38,  6, 46, 14, 54, 22, 62, 30,
   37,  5, 45, 13, 53, 21, 61, 29,
   36,  4, 44, 12, 52, 20, 60, 28,
   35,  3, 43, 11, 51, 19, 59, 27,
   34,  2, 42, 10, 50, 18, 58, 26,
   33,  1, 41,  9, 49, 17, 57, 25
};

/* expansion operation matrix
   plaintext_32bit_expanded_to_48bit_table的下标i表示目标位号(base 0),
   plaintext_32bit_expanded_to_48bit_table[i]表示源位号(base 1)。
   例如: plaintext_32bit_expanded_to_48bit_table[0]=4表示源位第3位(base 0)
   变成目标位第0位。
   数组plaintext_32bit_expanded_to_48bit_table的原内容如下:
   32,  1,  2,  3,  4,  5, 
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
   12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21,
   20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29,
   28, 29, 30, 31, 32,  1 
 */
byte plaintext_32bit_expanded_to_48bit_table[48] = 
{ /* 本数组已作修改, 函数f()须按照本数组对bufin进行扩展 */
    4, 25,  8, 28, 18,  1,
   11,  8, 25, 20, 24,  5,
   13, 32, 16,  1, 15, 23,
   26, 17, 17,  4,  6,  9,
   12, 22, 24, 12, 29, 29,
    5, 10, 30, 20, 19,  3,
   21,  2, 32, 21, 13,  7,
   16, 28, 31,  9, 14, 27
};


/* permuted choice table (key) */
byte key_perm_table[56] = 
{  /* The following bits are removed: 8, 16, 24, 32, 40, 48, 56, 64 */
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

/* number left rotations of key_perm_table */
byte key_rol_steps[16] = 
{
   1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28  /* 对原始密钥循环左移key_rol_steps[i]次得第i轮密钥(base 0) */
/* 1,1,2,2,2,2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 ; 设注释掉的第i个元素值为x, 那么x表示对上一轮密钥循环左移x次得本轮密钥
   1 2 3 4 5 6  7  8  9  10 11 12 13 14 15 16; round number
 */
};

/* permuted choice key (table) */
byte key_56bit_to_48bit_table[48] = /* bit 9,18,22,25,35,38,43,54 are removed */
{
   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};

/* The (in)famous S-boxes */
byte sbox[8][64] = 
{
   /* S1 */
   14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
   15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,

   /* S2 */
   15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
   13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,

   /* S3 */
   10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
   13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
   13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,

   /* S4 */
    7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
   13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
   10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,

   /* S5 */
    2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
   14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
   11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,

   /* S6 */
   12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
   10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
    9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
    4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,

   /* S7 */
    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
   13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,

   /* S8 */
   13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
    1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
    7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
    2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

/* 32-bit permutation function P used on the output of the S-boxes */
byte sbox_perm_table[32] = 
{   
   16,  7, 20, 21,
   29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8, 24, 14,
   32, 27,  3,  9,
   19, 13, 30,  6,
   22, 11,  4, 25
};
/* End of DES-defined tables */

/* Lookup tables initialized once only at startup by des_init() */
byte sbox_output_perm_table[8][64][4];
byte iperm[8][256][8];
byte fperm[8][256][8];
byte kn[16][8];

/* bit 0 is left-most in byte */
byte bytebit[8] = 
{
/* bit0  bit1  bit2  bit3  bit4  bit5  bit6  bit7 */
   0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

byte nibblebit[4] = 
{
   0x08, 0x04, 0x02, 0x01
};

void des_init(void)
{
   sbox_output_perm_table_init();
   perm_init(iperm, ip);
   perm_init(fperm, fp);
}


/* Set key (initialize key schedule array) */
void des_set_key(byte *key) /* 64 bits (will use only 56) */
{
   byte pc1m[56];      /* place to modify key_perm_table into */
   byte pcr[56];       /* place to rotate key_perm_table into */
   int i, j, b;

   /* Clear key schedule */
   memset(kn, 0, 16*8);
   /* 16轮, 每轮48位密钥分成8组, 每组6位存放到单个字节的右侧(左侧2位不用) */

   for (j=0; j<56; j++) /* convert key_perm_table to bits of key */
   {                    /* [%] j is the target bit number of key */
      b = key_perm_table[j] - 1;   /* integer bit location */
                                   /* [%] b is the source bit number of key, base 0 */     
      pc1m[j]=(key[b/8] & bytebit[b%8]) ? 1 : 0;/* find which key byte b is in */
                                                /* and which bit of that byte */
                                                /* and store 1-bit result as a byte */

   }
   for (i=0; i<16; i++) /* key chunk for each iteration */
   {  
      for(j=0; j<28; j++) /* [%] left half */
      {
         b = (j+key_rol_steps[i]) % 28;
         pcr[j] = pc1m[b];
      }
      for(j=28; j<56; j++) /* [%] right half */
      {
         b = 28 + (j-28+key_rol_steps[i]) % 28;
         pcr[j] = pc1m[b];
      }

      for (j=0; j<48; j++) /* select bits individually */
      {                    /* [%] Select 48 bits from 56 bits.
                                  j is the target bit number, and 
                                  key_56bit_to_48bit_table[j]-1 is 
                                  the source bit number */
         /* check bit that goes to kn[j] */
         if (pcr[key_56bit_to_48bit_table[j]-1]) /* [%] pcr[key_56bit_to_48bit_table[j]-1] is SourceBit, j is TargetBit */
         {
            /* mask it in if it's there */
            kn[i][j/6] |= bytebit[j%6] >> 2; /* [%] remove the trailing 2 bits
                                              j=0    1    2    3    4    5
                                     bytebit[b]=0x80 0x40 0x20 0x10 0x08 0x04
                                  bytebit[b]>>2=0x20 0x10 0x08 0x04 0x02 0x01
                                            */
         }
      } /* [%] for (j=0; j<48; j++) */
   } /* [%] for (i=0; i<16; i++) */
}


/* In-place encryption of 64-bit block */
void des_encrypt(byte *block)
{
   int i;
   byte work[8];       /* Working data storage */
   byte temp[4];

   permute(block, iperm, work);   /* Initial Permutation */

  /* Do the 16 rounds */
   for (i=0; i<=15; i++)
      round(i, work);

   /* Left/right half swap */
   memcpy(temp, work, 4);
   memcpy(work, work+4, 4);
   memcpy(work+4, temp, 4);

   permute(work, fperm, block);   /* Inverse initial permutation */
}

/* In-place decryption of 64-bit block */
void des_decrypt(byte *block)
{
   int i;
   byte work[8];   /* Working data storage */
   byte temp[4];

   permute(block, iperm, work);   /* Initial permutation */

   /* Do the 16 rounds in reverse order */
   for (i=15; i >= 0; i--)
      reverse_round(i, work);

   /* Left/right half swap */
   memcpy(temp, work, 4);
   memcpy(work, work+4, 4);
   memcpy(work+4, temp, 4);

   permute(work, fperm, block);   /* Inverse initial permutation */
}


/* Permute inblock according to perm, put result in outblock */
void permute(byte *inblock, byte perm[8][256][8], byte *outblock) 
{
//#1_begin------------
    if (perm == NULL)
   {
      memcpy(outblock, inblock, 8);
      return;
   }
   memset(outblock, 0, 8);

   int i, j;
   unsigned char *pin, *pout;
   unsigned char *p;

   pin = inblock;

   for (j = 0; j < 8; j ++ ) 
   {
      pout = outblock;
      
      p = perm[j][*pin++];
      
      for (i = 0; i < 8; i++) 
      {
         *pout++ |= *p++; 
      }
   }
                      // <--第1空, 请把解答写在#1_begin与#1_end之间
//#1_end==============
}

/* Do one DES cipher round */
/* i.e. the num-th one */
void round(int num, byte block[8])
{
   /* The rounds are numbered from 0 to 15. On even rounds
    * the right half is fed to f() and the result XORs
    * the left half; on odd rounds the reverse is done.
    */
   int i;
   byte result[4], *p;
   if(num % 2 == 0)
   {
      f(&block[4], kn[num], &result[0]);
      p = &block[0];
   } 
   else 
   {
      f(&block[0], kn[num], &result[0]);
      p = &block[4];
   }
   for(i=0; i<4; i++)
   {
      p[i] ^= result[i];
   }
}

void reverse_round(int num, byte block[8])
{
   /* The rounds are numbered from 15 to 0. On odd rounds
    * the right half is fed to f() and the result XORs
    * the left half; on even rounds the reverse is done.
    */
   int i;
   byte result[4], *p;
   if(num % 2 == 1)
   {
      f(&block[4], kn[num], &result[0]);
      p = &block[0];
   } 
   else 
   {
      f(&block[0], kn[num], &result[0]);
      p = &block[4];
   }
   for(i=0; i<4; i++)
   {
      p[i] ^= result[i];
   }
}

/* The nonlinear function f(), the heart of DES */
void f(byte bufin[4], byte subkey[8], byte bufout[4])
{
/* 函数f()须按照数组plaintext_32bit_expanded_to_48bit_table把32位bufin扩展成48位 */
//#2_begin------------
   byte help[8];
   for(int i=0 ; i < 8 ;i++)
   {
      help[i] = 0 ;
   }
   for(int i = 0 ; i < 4 ; i++)
   {
      bufout[i] = 0 ;
   }

   for(int i = 0 ; i < 48 ;i++)
   {
      int num = i / 6;
      int bit = i % 6;
      int cur = plaintext_32bit_expanded_to_48bit_table[i]-1;
      int old_num = cur / 8 ;
      int old_bit = cur % 8 ;
      help[num] |= ( ( ( bufin[old_num] >> ( 7 - old_bit ) ) &1 ) << ( 5 - bit ) ); 
   }
   //68 16 12 79 FA 6C F4 22

   for(int  i =  0 ;  i < 8 ; i++)
   {
      bufout[0] |= sbox_output_perm_table[i][ ( help[i] ^ subkey[i] ) &0x3f ][0];
      bufout[1] |= sbox_output_perm_table[i][ ( help[i] ^ subkey[i] ) &0x3f ][1];
      bufout[2] |= sbox_output_perm_table[i][ ( help[i] ^ subkey[i] ) &0x3f ][2];
      bufout[3] |= sbox_output_perm_table[i][ ( help[i] ^ subkey[i] ) &0x3f ][3];
   }
                      // <--第2空, 请把解答写在#2_begin与#2_end之间
//#2_end==============
}

/* initialize a perm array */
void perm_init(byte perm[8][256][8], byte p[64]) /* 64-bit, either init or final */
{
   int i, j, k;
   memset(perm, 0, 8*256*8); /* Clear the permutation array */
   for(i=0; i<8; i++) /* [%] i=SectionNum, each section contains 8 bits; */ 
   {
      for(j=0; j<256; j++) /* [%] j=SectionValue varying from 0 to 255; */ 
      {
         int j_bit, target_bit_num;
         for(j_bit=0; j_bit<8; j_bit++)
         {
            if((j & bytebit[j_bit]) == 0)
               continue;
            for(k=0; k<64; k++) /* 寻找跟源位号i*8+j_bit匹配的目标位号k */
            {
               if(p[k] - 1 == i*8 + j_bit)
                  break;
            }
            target_bit_num = k;
            perm[i][j][target_bit_num/8] |= bytebit[target_bit_num % 8];
         }
      }
   }
}

/* Initialize the lookup table for sbox's 6-bit input */
void sbox_output_perm_table_init(void)
{
   byte sbox_perm_table_inverse[32];
   int p, i, s, j, rowcol;
   int source_bit, target_bit;

   /* Compute sbox_perm_table_inverse, the inverse of sbox_perm_table.
    * This is easier to work with
    */
   for(p=0; p<32; p++) /* [%] p=SourceBit */
   {
      for(i=0; i<32; i++) /* [%] i=TargetBit */
      {
         if(sbox_perm_table[i]-1 == p) /* [%] sbox_perm_table[i] ranges within [1,32], so it is base 1, not base 0 */
         {
            sbox_perm_table_inverse[p] = i; /* [%] fill sbox_perm_table_inverse[p] with TargetBit=i */
            break;
         }
      }
   }

   for(s = 0; s < 8; s++) /* For each S-box */
   {
      for(i = 0; i < 64; i++) /* For each possible input(6 bits) */
      {      
         /* The row number is formed from the MSB and LSB,
          * while the column number is from the middle 4 bits
          */
         rowcol = (i & 0x20) | ((i & 1) ? 0x10 : 0x00) | ((i >> 1) & 0x0F);
         /* [%] rowcol = row*16 + col */
         for(j=0; j<4; j++) /* For each output bit */
         {   
            if(sbox[s][rowcol] & nibblebit[j]) /* [%] check bit 0,1,2,3 */
            {
               source_bit = s * 4 + j;
               target_bit = sbox_perm_table_inverse[source_bit];
               sbox_output_perm_table[s][i][target_bit/8] |= bytebit[target_bit%8];
            }
         }
      }
   }
}


int main()
{
   byte des_key[] = "ABCD1234";
   byte p[100] = "abcdefgh";
   byte c[100];
   int i;
   memset(c, 0, sizeof(c));
   des_init();
   des_set_key(des_key);
   memcpy(c, p, 8);
   des_encrypt(c);
   for(i=0; i<8; i++)
   {
      printf(i!=7 ? "%02X " : "%02X\n", c[i]);
   }
   des_decrypt(c);
   puts(c);
}
