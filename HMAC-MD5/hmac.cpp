#include <iostream>
#include <bitset>
#include "md5.h"
using namespace std;

bitset<8> ipad(0x36);
bitset<8> opad(0x5c);
int B1=64;
int L=16;
string key="key for hmac";
string msg="msg for hmac";

int main(){
	cout<<key<<endl;
	bitset<512> bit_key;

	// convert string to bit
	int size=key.length();
	for(int i=0;i<size;i++){
		bitset<8> tmp(key[i]);
		for(int j=0;j<8;j++){
			bit_key[j+(size-i-1)*8]=tmp[j];
		}
	}
	// cout<<bit_key<<endl;


	int size1=msg.length();
	bitset<512> bit_msg;
	for(int i=0;i<size1;i++){
		bitset<8> tmp(key[i]);
		for(int j=0;j<8;j++){
			bit_msg[j+(size1-i-1)*8]=msg[j];
		}
	}
	// cout<<bit_msg<<endl;




	// 64*8=512 bits
	bitset<512> bit_key512=bit_key;
	for(int i=0;i<size*8;i++){
		bit_key512[i+512-size*8]=bit_key[i];
	}
	for(int i=0;i<size*8;i++){
		bit_key512[i]=0;
	}
	// cout<<bit_key512<<endl<<endl;
	// generate ipad
	bitset<512> bit_ipad;
	for(int i=0;i<B1;i++){
		for(int j=0;j<8;j++){
			bit_ipad[i*8+j]=ipad[j];
		}
	}
	cout<<bit_ipad<<endl;
	// generate opad
	bitset<512> bit_opad;
	for(int i=0;i<B1;i++){
		for(int j=0;j<8;j++){
			bit_opad[i*8+j]=opad[j];
		}
	}
	cout<<bit_opad<<endl;

	// computer hmac
	// H(K XOR opad, H(K XOR ipad, text))
	// k is bit_key512, opad is bit_opad, ipad is bit_ipad, text is bit_msg
	bitset<128> tmp2(md5(bit_key512^bit_ipad));
	bitset<512> bit_tmp512;
	for(int i=0;i<512;i++){
		bit_tmp512[i+128]=bit_key512[i];
	}
	bitset<128> t=md5(bit_tmp512);
	cout<<t<<endl;




	// cout<<key^"a"<<endl;



	return 0;
}



