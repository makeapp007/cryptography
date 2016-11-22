#include <bitset>

#include "data.h"

word SubWord(word mes){
	word ret_val;
	for(int i=0;i<4;i++){
		bitset<4> high;
		bitset<4> low;
		for(int j=0;j<4;j++){
			low[j]=mes[j];
		}
		mes>>=4;
		for(int j=0;j<4;j++){
			high[j]=mes[j];
		}
		mes>>=4;
		bitset<8> store(S_Box[high.to_ulong()][low.to_ulong()]);
		for(int k=0;k<8;k++){
			ret_val[i*8+k]=store[k];
		}
	}

	// cout<<ret_val<<endl;
	return ret_val;
}
word RotWord(word mes){
	word ret_val;
	ret_val=mes>>24|mes<<8;
	// cout<<ret_val<<endl;
	return ret_val;
}

// 128 version: expand key to 44 words, 11round, each round 128 bits
void keyExpansion(byte key[4*Nk],word w[Nb*(Nr+1)]){
	word temp;
	int i=0;
// sequence , key1 is the highest eight bits
	while(i<Nk){
		w[i]=(key[4*i].to_ulong()<<24)+(key[4*i+1].to_ulong()<<16)+(key[4*i+2].to_ulong()<<8)+(key[4*i+3].to_ulong());
		i++;
	}
	// cout<<w[0]<<endl;

	i=Nk;
	while(i< Nb*(Nr+1)){
	// while(i==Nk){
		temp=w[i-1];
		if(i %Nk ==0){
			temp=SubWord(RotWord(temp)) ^ Rcon[i/Nk-1];
		}
		else if(Nk>6 and i % Nk ==4){
			temp=SubWord(temp);
		}
		w[i]=w[i-Nk] ^ temp;
		i++;
	}

}
void AddRoundKey(byte in[4*Nb],word key[4]){
	for(int i=0;i<4;i++){
		in[i]^=byte((key[i]>>24).to_ulong());
		in[i+4]^=(((key[i]<<8)>>24).to_ulong());
		in[i+8]^=(((key[i]<<16)>>24).to_ulong());
		in[i+12]^=(((key[i]<<24)>>24).to_ulong());
	}

}

void SubBytes(byte in[4*Nb]){
	for(int i=0; i<4*Nb; i++)
	{
		bitset<4> high;
		bitset<4> low;
		for(int j=0;j<4;j++){
			low[j]=in[i][j];
		}
		for(int j=0;j<4;j++){
			high[j]=in[i][j+4];
		}
		bitset<8> store(S_Box[high.to_ulong()][low.to_ulong()]);
		in[i]=store;

	}
}
byte GF(byte coeff, byte mes){
	bitset<16> px(0b0100011011);
	bitset<16> ax;
	for(int i=0;i<8;i++){
		ax[i]=mes[i];
	}
	bitset<16> tmp;
	for(int i=0;i<8;i++){
		if(coeff[i]==1){
			tmp^=(ax<<i);
		}
	}
	// ax=(ax<<1)^(ax<<2)^(ax<<3);
	ax=tmp;
	int power=0;
	while(ax.to_ulong()>=0x100){
		power=0;
		bitset<16> tmp=ax;
		while(tmp.to_ulong()>0){
			power++;
			tmp=tmp>>1;
		}
		// minus 9 is because x^8+x^4+x^3+x+1
		ax=(px<<(power-9))^ax;
	}	

	bitset<8> ret_val;
	for(int i=0;i<8;i++){
		ret_val[i]=ax[i];
	}

	return byte(ret_val.to_ulong());
}	

byte GF_naive(byte coeff, byte mes){
	bitset<16> px(0b0100011011);
	bitset<16> ax;
	for(int i=0;i<8;i++){
		ax[i]=mes[i];
	}
	if(coeff==0x02){
		if(mes.to_ulong()>0x80){
			ax=ax<<1;
			ax=ax^px;			
		}
		else{
			ax=ax<<1;			
		}
	}
	else if(coeff==0x03){
		if(mes.to_ulong()>0x80){
			bitset<16> tmp=ax<<1;
			ax=ax^tmp^px;
		}
		else{
			// no need to xor with px
			// ax=ax^px;						
			// ax=(ax<<1)^px;						
			// ax=ax^(ax<<1)^px;						
			// ax=ax^(px<<1);						
			// ax=(ax<<1)^(px<<1);						
			ax=ax^(ax<<1);
		}	
	}
	else if(coeff==0x0e){
		ax=(ax<<1)^(ax<<2)^(ax<<3);
		int power=0;
		while(ax.to_ulong()>=0x100){
			power=0;
			bitset<16> tmp=ax;
			while(tmp.to_ulong()>0){
				power++;
				tmp=tmp>>1;
			}
			ax=(px<<(power-9))^ax;
		}	
	}
	else if(coeff==0x01){
		ax=ax;
	}
	bitset<8> ret_val;
	for(int i=0;i<8;i++){
		ret_val[i]=ax[i];
	}
	// cout<<ret_val<<endl;

	return byte(ret_val.to_ulong());
}



// for debugging
void MixColumns2(byte in[4*Nb]){
	byte tmp[4];
	// cout<<Nb<<endl;
	for(int i=0; i<4; i++){
		// store since, since it will modify 
		for(int j=0; j<4; j++)
			tmp[j] = in[i+j*4];

		cout<<"tmp[0]:   "<<tmp[0]<<endl;
		cout<<GF(0x03, tmp[0]) <<endl;


		in[i]=GF(0x02, tmp[0]) ^ GF(0x02, tmp[1]) ^ tmp[2] ^ tmp[3];
		in[i+4]=tmp[0] ^ GF(0x02, tmp[1]) ^ GF(0x01, tmp[2]) ^ tmp[3];
		in[i+8]=tmp[0] ^ tmp[1] ^ GF(0x01, tmp[2]) ^ GF(0x01, tmp[3]);
		in[i+12]=GF(0x01, tmp[0]) ^ tmp[1] ^ tmp[2] ^ GF(0x01, tmp[3]);
	}
}

void MixColumns(byte in[4*Nb]){
	byte tmp[4];
	for(int i=0; i<4; i++){
		// store since, since it will modify 
		for(int j=0; j<4; j++)
			tmp[j] = in[i+j*4];

		in[i]=GF(0x02, tmp[0]) ^ GF(0x03, tmp[1]) ^ tmp[2] ^ tmp[3];
		in[i+4]=tmp[0] ^ GF(0x02, tmp[1]) ^ GF(0x03, tmp[2]) ^ tmp[3];
		in[i+8]=tmp[0] ^ tmp[1] ^ GF(0x02, tmp[2]) ^ GF(0x03, tmp[3]);
		in[i+12]=GF(0x03, tmp[0]) ^ tmp[1] ^ tmp[2] ^ GF(0x02, tmp[3]);
	}


}



void ShiftRows(byte in[4*Nb]){
	byte temp=in[4];
	// A
	in[4]=in[5];
	in[5]=in[6];
	in[6]=in[7];
	in[7]=temp;
	// B
	byte temp2;
	temp=in[8];
	temp2=in[9];
	in[8]=in[10];
	in[9]=in[11];
	in[10]=temp;
	in[11]=temp2;
	// C
	temp=in[12];
	temp2=in[13];
	in[12]=in[15];
	in[13]=temp;
	in[15]=in[14];
	in[14]=temp2;

}

void encrypt(byte in[4*Nb],byte out[4*Nb],word w[Nb*(Nr+1)]){
	word key[4];
	// for(int i=0;i<4;i++){
	// 	cout<<in[i]<<endl;
	// }

	for(int i=0;i<4;i++){
		key[i]=w[i];
	}
	// before round 1 

	AddRoundKey(in,key);
	// for(int i=0;i<4;i++){
	// 	cout<<in[i]<<endl;
	// }

	// start 10 rounds encryption
	for(int round=1;round<Nr;round++){
		SubBytes(in);
		ShiftRows(in);
		MixColumns(in);

		for(int i=0;i<4;i++){
			key[i]=w[round*Nb+i];
		}
		AddRoundKey(in,key);
	}
	// round 10
	SubBytes(in);
	ShiftRows(in);
	for(int i=0;i<4;i++){
		key[i]=w[Nb*Nr+i];
	}
	AddRoundKey(in,key);
	// out=in;
	for(int i=0;i<4*Nb;i++){
		out[i]=in[i];
	}

}
void InvSubBytes(byte in[4*Nb]){
	for(int i=0; i<4*Nb; i++){
		bitset<4> high;
		bitset<4> low;
		for(int j=0;j<4;j++){
			low[j]=in[i][j];
		}
		for(int j=0;j<4;j++){
			high[j]=in[i][j+4];
		}
		bitset<8> store(Inv_S_Box[high.to_ulong()][low.to_ulong()]);
		in[i]=store;
	}

};
void InvShiftRows(byte in[4*Nb]){
	byte temp=in[7];
	// A
	in[7]=in[6];
	in[6]=in[5];
	in[5]=in[4];
	in[4]=temp;
	// B
	byte temp2;
	temp=in[8];
	temp2=in[9];
	in[8]=in[10];
	in[9]=in[11];
	in[10]=temp;
	in[11]=temp2;
	// C
	temp=in[12];
	in[12]=in[13];
	in[13]=in[14];
	in[14]=in[15];
	in[15]=temp;
}
void InvMixColumns2(byte in[4*Nb]){
	byte tmp[4];
	for(int i=0; i<4; i++){
		// store since, since it will modify previous value
		for(int j=0; j<4; j++)
			tmp[j] = in[i+j*4];

		cout<<"tmp[0]:   "<<tmp[0]<<endl;
		cout<<GF(0x0e, tmp[0]) <<endl;



		in[i] = GF(0x0e, tmp[0]) ^ GF(0x0e, tmp[1]) ^ GF(0x0e, tmp[2]) ^ GF(0x0e, tmp[3]);
		in[i+4] = GF(0x0e, tmp[0]) ^ GF(0x0e, tmp[1]) ^ GF(0x0b, tmp[2]) ^ GF(0x0d, tmp[3]);
		in[i+8] = GF(0x0e, tmp[0]) ^ GF(0x09, tmp[1]) ^ GF(0x0e, tmp[2]) ^ GF(0x0b, tmp[3]);
		in[i+12] = GF(0x0b, tmp[0]) ^ GF(0x0d, tmp[1]) ^ GF(0x09, tmp[2]) ^ GF(0x0e, tmp[3]);
	}


}
void InvMixColumns(byte in[4*Nb]){
	byte tmp[4];
	for(int i=0; i<4; i++){
		// store since, since it will modify previous value
		for(int j=0; j<4; j++)
			tmp[j] = in[i+j*4];

		in[i] = GF(0x0e, tmp[0]) ^ GF(0x0b, tmp[1]) ^ GF(0x0d, tmp[2]) ^ GF(0x09, tmp[3]);
		in[i+4] = GF(0x09, tmp[0]) ^ GF(0x0e, tmp[1]) ^ GF(0x0b, tmp[2]) ^ GF(0x0d, tmp[3]);
		in[i+8] = GF(0x0d, tmp[0]) ^ GF(0x09, tmp[1]) ^ GF(0x0e, tmp[2]) ^ GF(0x0b, tmp[3]);
		in[i+12] = GF(0x0b, tmp[0]) ^ GF(0x0d, tmp[1]) ^ GF(0x09, tmp[2]) ^ GF(0x0e, tmp[3]);
	}


}


// just reverse the steps according to encrypt
void decrypt(byte in[4*Nb],byte out[4*Nb],word w[Nb*(Nr+1)]){
	word key[4];
	for(int i=0;i<4;i++){
		key[i]=w[Nb*Nr+i];
	}
	AddRoundKey(in,key);
	// for(int i=0;i<4;i++){
	// 	cout<<in[i]<<endl;
	// }

// start 10 rounds encryption
	for(int round=Nr-1;round>0;round--){
		InvShiftRows(in);
		InvSubBytes(in);

		for(int i=0;i<4;i++){
			key[i]=w[round*Nb+i];
		}
		AddRoundKey(in,key);
		InvMixColumns(in);

	}


// round 1
	InvShiftRows(in);
	InvSubBytes(in);
	for(int i=0;i<4;i++){
		key[i]=w[i];
	}
	AddRoundKey(in,key);

	// out=in;
	for(int i=0;i<4*Nb;i++){
		out[i]=in[i];
	}

	// for(int i=0;i<16;i++){
	// 	cout<<in[i]<<endl;
	// }

}



