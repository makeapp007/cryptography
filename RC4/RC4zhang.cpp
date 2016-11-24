#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
using namespace std;

void Initial(unsigned char*s, char*key){
	int i = 0, j = 0;
	unsigned char k[256] = {0};
	unsigned char tmp;
	for (i = 0; i<256; i++){
		s[i] = i;
		k[i] = key[i%strlen(key)];
	}
	for (i = 0; i<256; i++){
		j = (j + s[i] + k[i]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}

void Crypt(char* keystream,unsigned char*s,char*m){
	int i = 0; 
	int j = 0;
	int k = 0;
	unsigned char tmp;
	for (k = 0; k<strlen(m); k++){
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		keystream[k] = s[(s[i] + s[j]) % 256];
	}
}

int main(){
	char m[256] = {"testforRC4"};
	char key[256] = {"thisiskey"};
	char keystream[256] = {0};
	unsigned char S[256] = {0};
	char cipher[256]={0};
	unsigned char plain[256]={0};
	cout<<"This is the plain text: "<<m<<endl;
	cout<<"This is the key: "<<key<<endl;
	//the code below is to do the encryption
	Initial(S,key);
	Crypt(keystream, S, m);
	for (int i = 0; i<strlen(m); i++){
		cipher[i] = keystream[i]^m[i];
	}


	cout<<"This is the cipher text: "<<cipher<<endl;
printf("0x%x\n", cipher);

	//the code below is to do the decryption
	Initial(S,key);
	Crypt(keystream, S, cipher);
	for (int i = 0; i<strlen(cipher); i++){
		plain[i] = keystream[i]^cipher[i];
	}

	cout<<"This is the plain text: "<<plain<<endl;

	return 0;
}

