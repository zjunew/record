/***********************************************
 *                                             *
 * VC2019 调用 openssl 1.02g(32位)             *
 *                                             *
 *               Written by iceman@zju.edu.cn  *
 *                               Mar 25, 2024  *
 ***********************************************/

1. 找到vc2019自身的include及lib目录
① include
"C:\Windows Kits\10\Include\10.0.17763.0\ucrt\"
② lib
"C:\Windows Kits\10\Lib\10.0.17763.0\um\x86\"

2. 复制lib及include文件
xcopy /e /y include\openssl "C:\Windows Kits\10\Include\10.0.17763.0\ucrt\openssl\"  
xcopy lib\libeay32.lib "C:\Windows Kits\10\Lib\10.0.17763.0\um\x86\"
xcopy lib\ssleay32.lib "C:\Windows Kits\10\Lib\10.0.17763.0\um\x86\"

3. vc2019调用openssl库函数的演示程序
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


4. vc2019工程中调用32位openssl 1.02g库函数出错及处理
连接时若报以下错误:
error LNK2026: module unsafe for SAFESEH image.
处理措施:
Project->Properties->Linker->Advanced->Image Has Safe Exception Handlers->No
