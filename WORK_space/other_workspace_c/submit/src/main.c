
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/md5.h>
#include <openssl/rand.h>
#ifdef _MSC_VER
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#endif

void scan_hex(unsigned char *p, int n, unsigned char *q)
{
   int i;
   for(i=0; i<n; i++)
   {
      sscanf((char *)&p[i*2], "%02X", &q[i]);
   }
}

void dump_hex(unsigned char *p, int n, unsigned char *q)
{
   int i;
   for(i=0; i<n; i++)
   {
      sprintf((char *)&q[i*2], "%02X", p[i]);
   }
   q[i*2] = '\0';
}

int main()
{
	int i;
   char N0[0x101], E0[0x101], N1[0x101], D1[0x101];
   char cipher_text[0x101], sign_hex[0x101];
   unsigned char plain_text[0x101];
   unsigned char bufin[0x101], bufout[0x101], padded_md5[0x101], md5[0x101];
   gets(N0);
   gets(E0);
   gets(N1);
   gets(D1);
   gets(cipher_text);
   gets(sign_hex);

   /* Here is your code */
   //printf("2-----------------------------\n");
   //2---------------------------------------------------

   memset(plain_text, 0, sizeof(plain_text));
   memset(padded_md5, 0, sizeof(padded_md5));
   memset(md5, 0, sizeof(md5));
   RSA *prsa1,*prsa2;
   BIGNUM *pn0, *pe0, *pn1, *pd1;
   prsa1 = RSA_new();
   prsa2 = RSA_new();
   prsa1->flags |= RSA_FLAG_NO_BLINDING;
   prsa2->flags |= RSA_FLAG_NO_BLINDING;
   pn0 = BN_new();
   pe0 = BN_new();
   pn1 = BN_new();
   pd1 = BN_new();

   BN_hex2bn(&pn0, N0);
   BN_hex2bn(&pe0, E0);
   BN_hex2bn(&pd1, D1);
   BN_hex2bn(&pn1, N1);

   prsa1->n = pn1;
   prsa1->e = NULL;
   prsa1->d = pd1;
   
   int n = strlen(cipher_text)/2;
   memset(bufin, 0, sizeof(bufin));
   scan_hex((unsigned char *)cipher_text, n, bufin);
   memset(bufout, 0, sizeof(bufout));
   int plain_size = RSA_private_decrypt(n, bufin, bufout, prsa1, RSA_PKCS1_PADDING);
   //dump_hex(bufout, plain_size, plain_text);
   strncpy((char *)plain_text, (char *)bufout, plain_size);
   //2------------------------------------------------
   // printf("bufout = %s ",bufout);
   // printf("\nplain_text = %s, %d\n",plain_text , plain_size);

   // printf("\n3-----------------------------\n");
   //3-------------------------------------------
   BIGNUM *sign , *padded;
   sign = BN_new();
   padded = BN_new();
   BN_CTX *ctx;
   ctx = BN_CTX_new();
   n = BN_num_bytes(pn0);
   BN_hex2bn(&sign , sign_hex);
   BN_mod_exp(padded , sign , pe0 , pn0, ctx);
   n = BN_bn2bin(padded,padded_md5);
   BN_CTX_free(ctx);
   //3------------------------------------------
   //printf("n = %d\n padded_md5 = " , n) ;

   // for(i = 0 ; i < n ; i ++)
   // {
   //    printf("%02x" , padded_md5[i]);
   // }

   // printf("\n4-----------------------------\n");
   //4------------------------------------------------

   MD5(plain_text, plain_size, md5);
   // printf("md5 = ");
   // for(i = 0 ; i < 16 ; i++)
   //    printf("%02x ", md5[i]);
   // printf("\n padded_md5[0] = %02x\n",padded_md5[0]);

   if(padded_md5[0]==0x02 && n == 127)
   {
	  int j = 15 ;
      for(i = n-1 ; i >= n-16 ; i-- , j--)
      {
		  //printf("\npadded_md[%d] = %02x ,md5[%d] = %02x\n",i,padded_md5[i],j, md5[j]);
         if(padded_md5[i] != md5[j])
         {
            memset(plain_text, 0, plain_size);
            plain_size = 4 ;
            plain_text[0] = 'B' , plain_text[1] = 'A' ,plain_text[2] = 'D' ,plain_text[3] = '\0';
            break;
         }
		 //printf("%d\n",i);
      }
   }
   else
   {
	   //printf("\n in else\n");
      memset(plain_text, 0, plain_size);
      plain_size = 4 ;
      plain_text[0] = 'B' , plain_text[1] = 'A' ,plain_text[2] = 'D' ,plain_text[3] = '\0';
   }
   // printf("\nplain_text = %s" , plain_text);
	// printf("  size = %d" , strlen((char*)plain_text));
   // printf("\n5-----------------------------\n");
   //5-------------------------------------------------------

   prsa2->n = pn0;
   prsa2->e = pe0;
   prsa2->d = NULL;
   n = plain_size; 
   memset(bufin, 0, sizeof(bufin));
   memset(bufout, 0, sizeof(bufout));
   memset(cipher_text, 0, sizeof(cipher_text));
  
   n = RSA_public_encrypt(n, plain_text, bufout, prsa2, RSA_PKCS1_PADDING);
   
   dump_hex(bufout, n, (unsigned char *)cipher_text);

   // printf("\n6-----------------------------\n");
   //6---------------------------------------------

   MD5(plain_text,plain_size, md5);
   // printf("md5 = ");
   // for(i = 0 ; i < 16 ; i++)
   //    printf("%02x ", md5[i]);

   unsigned char sign_bin[0x101];
   memset(sign_bin, 0, sizeof(sign_bin));
   prsa1->n = pn1;
   prsa1->e = NULL;
   prsa1->d = pd1;
   n = RSA_size(prsa1)-112; 
   memset(bufin, 0, sizeof(bufin));
   memset(bufout, 0, sizeof(bufout));
   strncpy((char *)bufin, (char *)md5, n);
   n = RSA_private_encrypt(n, bufin, bufout, prsa1, RSA_PKCS1_PADDING);
   dump_hex(bufout, n,(unsigned char *) sign_hex);
	
   //printf("\n7-----------------------------\n");
   //7-------------------------------------------------------
   puts(cipher_text); /* ======================== */
   puts(sign_hex);    /* 程序最终要输出这2项,     */
                      /* 除此以外不可以有别的输出 */
                      /* ======================== */

   RSA_free(prsa1);
   RSA_free(prsa2);
   return 0;
}

