/***********************************************
 *                                             *
 * VC2019 ���� openssl 1.02g(32λ)             *
 *                                             *
 *               Written by iceman@zju.edu.cn  *
 *                               Mar 25, 2024  *
 ***********************************************/

1. �ҵ�vc2019�����include��libĿ¼
�� include
"C:\Windows Kits\10\Include\10.0.17763.0\ucrt\"
�� lib
"C:\Windows Kits\10\Lib\10.0.17763.0\um\x86\"

2. ����lib��include�ļ�
xcopy /e /y include\openssl "C:\Windows Kits\10\Include\10.0.17763.0\ucrt\openssl\"  
xcopy lib\libeay32.lib "C:\Windows Kits\10\Lib\10.0.17763.0\um\x86\"
xcopy lib\ssleay32.lib "C:\Windows Kits\10\Lib\10.0.17763.0\um\x86\"

3. vc2019����openssl�⺯������ʾ����
	#include <stdio.h>
	#include <string.h>
	#include <openssl/md5.h>
	#pragma comment(lib, "libeay32.lib")
	#pragma comment(lib, "ssleay32.lib")
	int main()
	{
		int i;
		unsigned char s[100] = "Hello", t[100];
		MD5_CTX m; //ctx:context
		MD5_Init(&m);
		MD5_Update(&m, s, strlen((char *)s));
		MD5_Final(t, &m);
		for (i = 0; i < 16; i++)
			printf("%02X ", t[i]);
	}


4. vc2019�����е���32λopenssl 1.02g�⺯����������
����ʱ�������´���:
error LNK2026: module unsafe for SAFESEH image.
�����ʩ:
Project->Properties->Linker->Advanced->Image Has Safe Exception Handlers->No
