/************************************************************************
 * RSA加密解密函数
 *
 * file: test_rsa_encdec.c
 * gcc -Wall -O2 -o test_rsa_encdec test_rsa_encdec.c -lcrypto -lssl
 *
 * author: tonglulin@gmail.com by www.qmailer.net
 * new author : 曾润良
 ************************************************************************/
#pragma once
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>
#define BUFFSIZE 4096

using namespace std;
//加密类
class my_encrypt{
	public:
         char *str;//src
         char *en;//en
	public:
         my_encrypt(  char *src):en(NULL)
	{
		RSA *rsa = NULL;
		FILE *fp = NULL;
        str = new  char[strlen(src) + 1];
        strcpy(str,src);
		int len = 0;
		int rsa_len = 0;

        if ((fp = fopen("D:\\pubkey.pem", "r")) == NULL) {
			cout<<"pubkey open failed"<<endl;
			return ;
		}

		/* 读取公钥PEM，另一种PUBKEY格式PEM使用PEM_read_RSA_PUBKEY函数*/

		if ((rsa = PEM_read_RSAPublicKey(fp, NULL, NULL, NULL)) == NULL) {
			cout<<"pem read error"<<endl;
			return ;
		}

        //RSA_print_fp(stdout, rsa, 0);

		len = strlen(str);
		rsa_len = RSA_size(rsa);

        en = ( char *)malloc(rsa_len + 1);
		memset(en, 0, rsa_len + 1);

		if (RSA_public_encrypt(rsa_len, (unsigned char *)str, (unsigned char*)en, rsa, RSA_NO_PADDING) < 0) 
		{
			cout<<"rsa public encrypt"<<endl;
			return;
		}

		RSA_free(rsa);
		fclose(fp);
	}
		~my_encrypt()
		{
			if(en != NULL){
				free(en);
				en = NULL;
			}
            delete []str;
            str = NULL;
		}
};

