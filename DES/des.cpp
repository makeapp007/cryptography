#include <iostream>
#include <bitset>
#include "des.h"
#include <math.h>
using namespace std;

extern bitset<48> subKey[16];


int main(){
	// string message="children";
	string message="Welcome to Des";
	string key="together";
	// string message="helloooo";
	// string key="together";
	// string message;
	// cin>>message;

//change key to 64bits 
	bitset<64> bit_key=strTObit(key); 
	// cout<<"bit_key is  "<<bit_key<<endl;
// change message to 64bits
	// cout<<message.size()<<endl;
	// cout<<ceil(float(message.size())/8)<<endl;

// encrypting every eight bits
	for(int i=0;i<ceil(float(message.size())/8);i++){
		string message8;
		int actualsize;
		if(message.size()>=8){
			actualsize=8;
		}
		else{
			actualsize=message.size()-message.size()/8*8;
		}
		for(int j=0;j<actualsize;j++){
			message8+=message[j+i*8];
		}
		// cout<<message8<<endl;

// change string to bit
		bitset<64> bit_message=strTObit(message8); 
		// cout<<"bit message is "<< bit_message<<endl;

// encrypting message
		bitset<64> encrypt_mes=encrypt(bit_message,bit_key);
		// cout<<"encrypted message: "<< encrypt_mes<<endl;
		string cip_message=binaryToascii(encrypt_mes);
		cout<<"ciphertext is "<<cip_message<<endl;

	// decrypting message
		bitset<64> decrypt_mes=decrypt(encrypt_mes,bit_key);
		// cout<<"decrypted message: "<< decrypt_mes<<endl;
	// convert binary to ascii
		string ori_message=binaryToascii(decrypt_mes);
		cout<<"plaintext is "<<ori_message<<endl;
	}	



	return 0;
}



