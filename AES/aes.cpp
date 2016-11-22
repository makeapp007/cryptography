//128-bits key encryption 
#include <iostream>
#include <bitset>
#include "aes.h"
using namespace std;





int main(){
	byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 
					0x28, 0xae, 0xd2, 0xa6, 
					0xab, 0xf7, 0x15, 0x88, 
					0x09, 0xcf, 0x4f, 0x3c};
	cout<<"private key is: "<<endl;
	for(int i=0;i<16;i++){
		cout<<hex<<key[i].to_ulong()<<" ";
	}
	cout<<endl;


	byte plain[16] = {0x32, 0x88, 0x31, 0xe0, 
					0x43, 0x5a, 0x31, 0x37,
					0xf6, 0x30, 0x98, 0x07,
					0xa8, 0x8d, 0xa2, 0x34}; 
	cout<<"plaintext is: "<<endl;
	for(int i=0;i<16;i++){
		cout<<hex<<plain[i].to_ulong()<<" ";
	}
	cout<<endl;

// key schedule
	word w[Nb*(Nr+1)];
	keyExpansion(key,w);	
	// cout<<"key expansion result: "<<endl;
	// for(int i=0;i<Nb*(Nr+1);i++){
	// 	cout<<w[i]<<endl;
	// }

// change plaintext to matrix
	byte cipher[4*Nb];
	encrypt(plain,cipher,w);

	cout<<"ciphertext is: "<<endl;
	for(int i=0; i<16; ++i){
		cout << hex << cipher[i].to_ulong() << " ";
		if((i+1)%4 == 0)
			cout << endl;
	}
	cout << endl;

	byte decrypt_mes[4*Nb];
	decrypt(cipher,decrypt_mes,w);
	cout<<"decrypt mes is: "<<endl;
	for(int i=0; i<16; ++i){
		cout << hex << decrypt_mes[i].to_ulong() << " ";
		if((i+1)%4 == 0)
			cout << endl;
	}
	cout << endl;




	return 0;
}


