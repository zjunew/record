#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/bn.h>
#include <openssl/ec.h>

#ifdef _MSC_VER
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#endif

#define A  "-3"                                               /* coefficient a */
        /* "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFC" is equal to "-3" */
#define B  "64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1" /* coefficient b */
#define P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF" /* mod P=192-bit */
#define GX "188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012" /* base point G's */
#define GY "07192B95FFC8DA78631011ED6B24CDD573F977A11E794811" /* coordinates(Gx,Gy) */
#define N  "FFFFFFFFFFFFFFFFFFFFFFFF99DEF836146BC9B1B4D22831" /* order N=192-bit */
#define D  "CADDC27FEFC3040C1CCA194542218E002F58D504A639B668" /* private key D */

void dump_hex(unsigned char *p, int n, unsigned char *q)
{
   int i;
   for(i=0; i<n; i++)
   {
      sprintf((char *)&q[i*2], "%02X", p[i]);
   }
   q[i*2] = '\0';
}

void scan_hex(unsigned char *p, int n, unsigned char *q)
{
   int i;
   for(i=0; i<n; i++)
   {
      sscanf((char *)&p[i*2], "%02X", &q[i]);
   }
}


int ecc_encrypt_decrypt(void)
{
   unsigned char plaintext[256] = "A QuickBrownFox+ALazyDog"; /* 24字节=192位 */
   unsigned char ciphertext[512];
   unsigned char bufin[256];
   unsigned char bufout[256];
   unsigned char hex[256];
   long ticks;
   int  text_len;
   EC_GROUP *group;
   BN_CTX *ctx;
   EC_POINT *G, *T, *R;       /* G是基点, T是临时点, R是公钥点 */
   BIGNUM *p, *a, *b, *n, *gx, *gy, *tx, *ty;
   BIGNUM *m, *d, *k, *r, *s; /* m是明文, d是私钥, k是随机数, r及s是密文 */

   p = BN_new();
   a = BN_new();
   b = BN_new();  /* a,b,p决定曲线 */
   n = BN_new();  /* n是基点G的阶 */
   gx = BN_new(); /* 基点G的x坐标 */
   gy = BN_new(); /* 基点G的y坐标 */
   tx = BN_new(); /* 临时点T的x坐标 */
   ty = BN_new(); /* 临时点T的y坐标 */
   m = BN_new();  /* m是明文 */
   d = BN_new();  /* d是私钥 */
   k = BN_new();  /* k是随机数 */
   r = BN_new();  /* r是密文第1部分 */
   s = BN_new();  /* s是密文第2部分 */


   BN_hex2bn(&a, A);
   BN_hex2bn(&b, B);
   BN_hex2bn(&p, P);
   BN_hex2bn(&n, N);
   BN_hex2bn(&gx, GX);
   BN_hex2bn(&gy, GY);
   BN_hex2bn(&d, D);

   group = EC_GROUP_new(EC_GFp_mont_method()); /* 或EC_GFp_simple_method(); mont: BN_mod_mul_montgomery */
   ctx = BN_CTX_new();
   EC_GROUP_set_curve_GFp(group, p, a, b, ctx);

   G = EC_POINT_new(group);
   EC_POINT_set_affine_coordinates_GFp(group, G, gx, gy, ctx);
   EC_GROUP_set_generator(group, G, n, BN_value_one()); /* 基点=G, G的阶=n, 余因子=1 */

   R = EC_POINT_new(group);
//#1_begin------------
   EC_POINT_mul(group, R, d, NULL, NULL, ctx)                  ; // <--第1空, 请把解答写在分号左边, 限填1条语句; 本行上方切勿插入空行
//#1_end==============
   EC_POINT_get_affine_coordinates_GFp(group, R, tx, ty, ctx); /* tx = (d*G).x */
   ticks = (long)time(NULL);
   RAND_add(&ticks, sizeof(ticks), 1); /* srand() */
   BN_rand(k, BN_num_bits(n), 0, 0);   /* 产生随机数k, 位数与n相等 */
//#2_begin------------
   T = EC_POINT_new(group)                 ; // <--第2空, 请把解答写在分号左边, 限填1条语句; 本行上方切勿插入空行
//#2_end==============
   EC_POINT_mul(group, T, k, NULL, NULL, ctx); /* T = k*G */

   EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx); /* tx = (k*G).x */

   BN_copy(r, tx); /* r = 密文第1部分 = (k*G).x; 注意(k*G).x不可以mod n */

   EC_POINT_mul(group, T, NULL, R, k, ctx); /* T = k*R = k*d*G */
   EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx); /* tx = (k*R).x */

   BN_bin2bn(plaintext, BN_num_bytes(n), m); /* m = plaintext */
   BN_mod_mul(s, m, tx, n, ctx); /* s = 密文第2部分 = m * (k*R).x mod n */

   EC_POINT_set_compressed_coordinates_GFp(group, T, r, 0, ctx); /* T=k*G;
                                                                    其中T的x坐标=r,
                                                                    y坐标自动计算 */
   EC_POINT_mul(group, T, NULL, T, d, ctx); /* T = d*k*G */
   EC_POINT_get_affine_coordinates_GFp(group, T, tx, ty, ctx); /* tx = (d*k*G).x */
//#3_begin------------
   BN_mod_inverse(tx,tx,n,ctx)                  ; // <--第3空, 请把解答写在分号左边, 限填1条语句; 本行上方切勿插入空行
//#3_end==============
   BN_clear(m);
   BN_mod_mul(m, s, tx, n, ctx); /* m = s/(d*r).x = m * (k*R).x / (k*R).x = m */
   memset(bufout, 0, sizeof(bufout));
   text_len = BN_bn2bin(m, bufout);
   memset(hex, 0, sizeof(hex));
   dump_hex(bufout, text_len, hex);
   puts((char *)hex); /* 输出 "4120517569636B42726F776E466F782B414C617A79446F67" */
   BN_free(p);
   BN_free(a);
   BN_free(b); 
   BN_free(n); 
   BN_free(gx);
   BN_free(gy);
   BN_free(tx);
   BN_free(ty);
   BN_free(m); 
   BN_free(d); 
   BN_free(k); 
   BN_free(r); 
   BN_free(s); 
   EC_POINT_free(G);
   EC_POINT_free(R);
   EC_POINT_free(T);
   BN_CTX_free(ctx);
   EC_GROUP_free(group);
   return !strcmp((char *)bufout, (char *)plaintext);
}


int main()
{   
   if(ecc_encrypt_decrypt())
      puts("Yes");
   else
      puts("No");
   return 0;
}
