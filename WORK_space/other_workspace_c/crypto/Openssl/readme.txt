
(1) lib\libeay32.lib��lib\ssleay32.lib���Ѿ�����õ�VC6���õľ�̬��,
    ֻҪ���������ļ�����VC6��libĿ¼�м��ɡ�
(2) include\openssl��openssl��ص�ͷ�ļ�, ֻҪ��openssl����ļ��и��Ƶ�
    VC6��includeĿ¼�м���, ע���ǰ�openssl�ļ��м�������ļ������ƹ�ȥ��
(3) VC6д��Դ����Ҫ����Openssl�⺯��ʱ����Ҫ����������:
    ����main()ǰ���������#include���
    #include <openssl/xxx.h> /*����xxx.h��ĳ���㷨��ص�.h�ļ�����des.h, md5.h */  
    ����main()ǰ���������#pragma���
    #pragma comment(lib, "libeay32.lib")
    #pragma comment(lib, "ssleay32.lib")



