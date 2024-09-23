#ifdef _MSC_VER
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#endif

#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

#if 2147483647L+1L == -2147483648L 
typedef long long32;
typedef unsigned long ulong32;
#else
typedef int long32;           /* In 64-bit systems, long may be 64-bit, */
typedef unsigned int ulong32; /* here we force it to be 32-bit. */
#endif

unsigned char sbox[8][64] = 
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

#if 0
typedef struct MD5state_st
{                    // 这是openssl源代码中定义的MD5_CTX结构,供复制16字节md5值到d时参考
	ulong32 A,B,C,D;  // 4个state
	ulong32 Nl,Nh;    // Nl是报文位长度的低32位，Nh是报文位长度的高32位
	ulong32 data[64]; // 64字节buffer
	unsigned int num; // data中残留的尚未处理的字节数
} MD5_CTX;
#endif
void stepthree(unsigned char *re ,unsigned char *k)
{
   //static int flag  = 2;//
   char help[9];
   for(int  i = 0 ;i < 8 ; i++)
   {
      int first = (re[i]>>5)*2+ (re[i]&1);
      int second = (re[i] & 30)>>1;
      int tar = first * 16 + second;
      help[i] = sbox[i][tar];
      //debug
      // if(flag)
      // {
      //    printf("%d ",re[i]);
      //    printf("%d %d ",first , second);
      //    printf("%d \n",help[i]);
      //    flag--;
      // }
      
   }   
   for (int  i = 0 ;i < 4 ;i++)
   {
      k[i] = help[i*2] *16 + help[i*2 + 1];
   }
  
   
}

void get_md5_hash(MD5_CTX *ctx, unsigned char *md5_hash) {  
    md5_hash[0] = ctx->A & 0xFF;  
    md5_hash[1] = (ctx->A >> 8) & 0xFF;  
    md5_hash[2] = (ctx->A >> 16) & 0xFF;  
    md5_hash[3] = (ctx->A >> 24) & 0xFF;  
    md5_hash[4] = ctx->B & 0xFF;  
    md5_hash[5] = (ctx->B >> 8) & 0xFF;  
    md5_hash[6] = (ctx->B >> 16) & 0xFF;  
    md5_hash[7] = (ctx->B >> 24) & 0xFF;  
    md5_hash[8] = ctx->C & 0xFF;  
    md5_hash[9] = (ctx->C >> 8) & 0xFF;  
    md5_hash[10] = (ctx->C >> 16) & 0xFF;  
    md5_hash[11] = (ctx->C >> 24) & 0xFF;  
    md5_hash[12] = ctx->D & 0xFF;  
    md5_hash[13] = (ctx->D >> 8) & 0xFF;  
    md5_hash[14] = (ctx->D >> 16) & 0xFF;  
    md5_hash[15] = (ctx->D >> 24) & 0xFF;  
}
int main()
{
   int i, j, n;
   unsigned char p[0x100], c[0x100], iv[0x11];
   unsigned char data[0x40], d[0x20], k[0x20], x;
   MD5_CTX m;
   scanf("%s",iv); // iv长度固定为16字节
   scanf("%s",p);  // p的长度不会超过0xFF
   n = strlen(p);
   
   //int flag = 1;//debug
   for(i=0; i<n; i++)
   {
      int count ;
      for(count = 0 ; count < 16 ; count++)
      {
         data[count] = iv[count];
      }
      data[count] = 0xFF;
      count++;
      for (;count <64;count ++)
      {
         data[count] = 0x00;
      }
      
      data[56]= 0x10;
      
      // if(flag)
      // {
      //    for(int m = 0 ; m<20 ;m++)
      //    {
      //       printf("%x ",data[m]);
      //    }
      //    printf("\n");
      // }
      
      //2
      MD5_Init(&m);
      MD5_Update(&m , data ,0x40);
      //MD5_Final(d,&m);错
      get_md5_hash(&m,d);

      //debug
      // if(flag)
      // {printf("    d printf:\n");
      // for(int m = 0 ; m < 16 ; m++)
      // {
         
      //    printf("%X ",d[m]);
      // }
      // printf("\n");}

      //3
      
      
      // unsigned long xl = 0,xh = 0;
      // for (int help = 0; help < 3; help++) {
      //    xl |= (unsigned long)d[help] << (help * 8);
      //    xh |= (unsigned long)d[help+3] << (help * 8);
      // }
      
      
      unsigned char re[9] ;
      memset(re,0,sizeof(re));
      re[0] = d[0] >> 2;
      //if(flag)
      //printf("%x",d[0]&3);
      re[1] = (d[1]>>4) +(d[0]&3)*16;
      re[2] = (d[1]&15)*4 + (d[2]>>6);
      re[3] = (d[2]&63);
      
      re[4] = d[3]>>2 ;
      re[5] = (d[4]>>4) + (d[3]&3)*16;
      re[6] = (d[4]&15)*4 + (d[5]>>6);
      re[7] = (d[5]&63);
      
      stepthree(re,k);
      //if(flag)
      // {
      //    printf("\n%x\n",re[0]);
      //    printf("%x  %x\n",re[1],re[2]);
      // }
      // 
      // for(int help = 0 ;help < 4; help++)
      // {
      //    re[help] = (xl & 0x3f);
      //    xl>>=6;
      //    stepthree(re , k);
      // }
      // for(int help = 4 ;help < 8; help++)
      // {
      //    re[help] = (xh & 0x3f);
      //    xh>>=6;
      //    stepthree(re , k);
      // }


      // if(flag)
      // {printf("    k printf:\n");
      // for(int m = 0 ; m < 4 ; m++)
      // {
         
      //    printf("%x ",k[m]);
      // }
      // printf("\n");}

      //4
      x=0;
      for(int help = 0 ; help < 4 ;help++)
      {
         x += k[help];
      }
      
      // if(flag)
      //    printf("%X\n",x);
      //5
      c[i] = p[i] ^ x ;   

      //6

      for(int help = 0 ;help <15 ; help++)
      {
         iv[help]  = iv[help+1];
      }  
      iv[15] = c[i]; 

      // flag = 0;
     
   }
   for(i=0; i<n; i++)
   {
      printf((i+1)%0x10==0 ? "%02X\n":"%02X ", c[i]);
   }
   return 0;
}

