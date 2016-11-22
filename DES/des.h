#include <bitset>
#include "data.h"


using namespace std;
bitset<48> subKey[16];



bitset<64> strTObit(string input_mes){
	bitset<64> final; 
	for(int i=0;i<8;i++){
		bitset<8> tmp=bitset<8>(input_mes[i]);
		// cout<<tmp<<endl;
		for(int j=0;j<8;j++){
			final[i*8+j]=tmp[j];

		}
	}	
	return final;
}
bitset<64> initial_permutation(bitset<64> input_bit){
	bitset<64> final;
// highest bit is x1, y1
	for(int i=0;i<64;i++){
		final[63-i]=input_bit[64-IP[i]];
	}
	return final;
}

// generating K1 
// passing it using by reference &, so that change key56 each round
bitset<48> key_schedule(bitset<56> &input_bit,int shift){
	// cout<<"start generating k1"<<endl;
	bitset<48> bit_key48;
// key shift
	int shiftamt=num_leftshift[shift];


	// cout<<(final<<28)<<endl;
	// cout<<(final>>28)<<endl;
	// cout<<"start shifting "<<endl;
	if(shiftamt==1){
		int lstart=input_bit[55];
		int rstart=input_bit[27];
		input_bit=input_bit<<1;
		input_bit[0]=rstart;
		input_bit[28]=lstart;
	}
	else if(shiftamt==2){
		int lstart1=input_bit[55];
		int lstart2=input_bit[54];
		int rstart1=input_bit[27];
		int rstart2=input_bit[26];
		input_bit=input_bit<<2;
		input_bit[1]=rstart1;
		input_bit[0]=rstart2;
		input_bit[29]=lstart1;
		input_bit[28]=lstart2;
	}	
	// cout<<"finish shifting"<<endl;
// PC2 
	for(int i=0;i<48;i++){
		bit_key48[47-i]=input_bit[56-PC2[i]];
	}
	return bit_key48;
}

bitset<64> encrypt(bitset<64> bit_message,bitset<64> bit_key){

	// doing initial_permutation
	bitset<64> per_mes=initial_permutation(bit_message);
	// cout<<"per_mes: "<<per_mes<<endl;


// in F function, start encrypting
// get R0,R1 from permutation message
	bitset<32> R0((per_mes.to_ulong()&0xFFFFFFFF));

	bitset<32> L0((per_mes.to_ulong()>>32)&0xFFFFFFFF);
	// cout<<"R0 is : "<<R0<<endl;
	// cout<<"L0 is : "<<L0<<endl;

	bitset<32> R1;
	bitset<32> L1;

// doing key schedule1
// PC1, change 64 bits to 56bits
		bitset<56> bit_key56;
		for(int i2=0;i2<56;i2++){
			bit_key56[55-i2]=bit_key[64-PC1[i2]];
		}
// cout<<"after PC1: "<<bit_key56<<endl;

	for(int i=0;i<16;i++){
// doing right message expansion
		bitset<48> Rexpansion;
		for(int j=0;j<48;j++){
			Rexpansion[47-j]=R0[32-E[j]];
		}
// doing key schedule2

		bitset<48> bit_key48=key_schedule(bit_key56,i);
		// cout<<"key schedule result  "<<i<<"  "<<bit_key48<<endl;

// key expansion
		Rexpansion=Rexpansion^bit_key48;
		// cout<<"Rexpansion: "<<Rexpansion<<endl;
// s box
		bitset<32> boxout;
		for(int jj=7;jj>=0;jj--){
// i guess s8 is in the back
// standard way, calculate s1,s2...  
			bitset<2> row;
			row[1]=Rexpansion[5];
			row[0]=Rexpansion[0];
			bitset<4>	col;
			col[0]=Rexpansion[1];
			col[1]=Rexpansion[2];
			col[2]=Rexpansion[3];
			col[3]=Rexpansion[4];
			// cout<<"row : "<<row.to_ulong()<<endl;

			int four_int=S_BOX[jj][row.to_ulong()][col.to_ulong()];
			bitset<4> four_bit(four_int);
			// cout<<"fourbit num"<<four_int<<endl;

			boxout[31-jj*4]=four_bit[3];
			boxout[31-jj*4-1]=four_bit[2];
			boxout[31-jj*4-2]=four_bit[1];
			boxout[31-jj*4-3]=four_bit[0];
			Rexpansion=Rexpansion>>6;
		}
		// cout<<"boxout: "<<boxout<<endl;
		bitset<32> p_boxout;
		for(int i1=0;i1<32;i1++){
			p_boxout[31-i1]=boxout[32-P[i1]];
		}
// done f
		L1=R0;
		R1=L0^p_boxout;
		L0=L1;
		R0=R1;

	}
// get the f output, 64 bits, change L0, RO
	bitset<64> final;
	for(int i=32;i<64;i++){
		final[i]=R0[i-32];
	}
	for(int i=0;i<32;i++){
		final[i]=L0[i];
	}

	// cout<<"before IP-1: "<<final<<endl;
// final step, IP swap
// pay attention to the table, x1,y1 is the highest bit
	bitset<64> encrypt;
	for(int i=0;i<64;i++){
		encrypt[63-i]=final[64-IP_SW[i]];
	}

	return encrypt;
}


void generateKeys(bitset<64> bit_key){
	bitset<56> bit_key56;
	for(int i2=0;i2<56;i2++){
		bit_key56[55-i2]=bit_key[64-PC1[i2]];
	}
	for(int i=0;i<16;i++){
		bitset<48> bit_key48=key_schedule(bit_key56,i);
		// cout<<"bit_key48 is "<<bit_key48<<endl;
		subKey[i]=bit_key48;
	}


}

string binaryToascii(bitset<64> decrypt_mes){
// convert binary to ascii
	string ori_message;
	while(decrypt_mes.count()){
		bitset<8> tmp;
		for(int i=0;i<8;i++){
			tmp[i]=decrypt_mes[i];
		}
		char aChar =  tmp.to_ulong();
		ori_message=ori_message+aChar;
		decrypt_mes=decrypt_mes>>8;
	}
	return ori_message;
}


bitset<64> decrypt(bitset<64> encrypt_mes,bitset<64> bit_key){
	bitset<64> final;
	for(int i=0;i<64;i++){
		final[63-i]=encrypt_mes[64-IP[i]];
	}
	// cout<<"final is "<<final<<endl;
	bitset<32> L0;
	bitset<32> R0;
	bitset<32> L1;
	bitset<32> R1;
// because L0 and R0 was swapped in the last step
	for(int i=32;i<64;i++){
		L0[i-32]=final[i];
	}
	for(int i=0;i<32;i++){
		R0[i]=final[i];
	}
	// cout<<"L0: "<<L0<<endl;	

// i didn't save key each round, but for decrypting, i have to use K16 at first
// so i have to run key schedule from k1 to k16 first 

// doing key schedule1
// PC1, change 64 bits to 56bits
	generateKeys(bit_key);



// starting 16 rounds descrption
// almost the same with encryption	
	for(int i=0;i<16;i++){
// doing right message expansion

		bitset<48> Rexpansion;

		for(int j=0;j<48;j++){
			Rexpansion[47-j]=R0[32-E[j]];
		}
// doing key schedule2

		bitset<48> bit_key48=subKey[15-i];
		// cout<<"key schedule result  "<<i<<"  "<<bit_key48<<endl;

// key expansion
		Rexpansion=Rexpansion^bit_key48;
		// cout<<"Rexpansion: "<<Rexpansion<<endl;
// s box
		bitset<32> boxout;
		for(int jj=7;jj>=0;jj--){
// i guess s8 is in the back
// standard way, calculate s1,s2...  
			bitset<2> row;
			row[1]=Rexpansion[5];
			row[0]=Rexpansion[0];
			bitset<4>	col;
			col[0]=Rexpansion[1];
			col[1]=Rexpansion[2];
			col[2]=Rexpansion[3];
			col[3]=Rexpansion[4];
			// cout<<"row : "<<row.to_ulong()<<endl;

			int four_int=S_BOX[jj][row.to_ulong()][col.to_ulong()];
			bitset<4> four_bit(four_int);
			// cout<<"fourbit num"<<four_int<<endl;

			boxout[31-jj*4]=four_bit[3];
			boxout[31-jj*4-1]=four_bit[2];
			boxout[31-jj*4-2]=four_bit[1];
			boxout[31-jj*4-3]=four_bit[0];
			Rexpansion=Rexpansion>>6;
		}
		// cout<<"boxout: "<<boxout<<endl;
		bitset<32> p_boxout;
		for(int i1=0;i1<32;i1++){
			p_boxout[31-i1]=boxout[32-P[i1]];
		}
// done f
		L1=R0;
		R1=L0^p_boxout;
		L0=L1;
		R0=R1;


	}

	// cout<<"L0 is "<<L0<<endl;
	// cout<<"R0 is "<<R0<<endl;

	bitset<64> per_message;
	for(int i=32;i<64;i++){
		per_message[i]=R0[i-32];
	}
	for(int i=0;i<32;i++){
		per_message[i]=L0[i];
	}
	// cout<<"bit_message: "<<per_message<<endl;

	bitset<64> bit_message;
	for(int i=0; i<64; i++){
		bit_message[63-i] = per_message[64-IP_SW[i]];
	}

	return bit_message;
}








