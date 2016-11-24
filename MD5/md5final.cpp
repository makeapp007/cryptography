// md5中有很多都是用小端的，这个我没看到，导致查了很久的bug
// reverse function is for change the big endian to little endian
// it only support input less than 512bits. if more ,you should use a for loop 


#include <stdlib.h>
#include <bitset>
#include <string.h>
#include <iostream>
#include "math.h"
using namespace std;
 
// uint32_t state[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
#define shift(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))    
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))


 
unsigned int reverse(  unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));

}
const unsigned s[64] = { 	
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 
};


 // 𝑇_𝑖_=𝐅𝐥𝐨𝐨𝐫(4294967296∗|_sin__𝑖__|)
const unsigned T[64] = {	
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,				
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

	// unsigned int A = 0x01234567;   //A
	// unsigned int B = 0x89abcdef;
	// unsigned int C = 0xfedcba98;
	// unsigned int D = 0x76543210;   //D
//  because this use little endian, so it should be the following
	unsigned int A = 0x67452301;   //A
	unsigned int B = 0xefcdab89;   //B
	unsigned int C = 0x98badcfe;   //C
	unsigned int D = 0x10325476;   //D


int main() {

	// string plaintext="hello this is message digest 5";
	string plaintext="hello this is message digest 5. Good job";
	cout<<"plaintext is:  "<<endl<<plaintext<<endl;
	// cout<<plaintext.length()<<endl;
	// change string to bit
	// cout<<plaintext.length()/8<<endl;

	// suppose the mes is smaller than 512 bits
	bitset<512> bit_mes;
	// int high=ceil(float(plaintext.length())/8);
	int size=plaintext.length();
	for(int i=0;i<size;i++){
		// cout<<i<<endl;
		bitset<8> tmp(plaintext[i]);
		for(int j=0;j<8;j++){
			bit_mes[j+(size-i-1)*8]=tmp[j];
		}
	}

	// cout<<bit_mes<<" "<<endl;
	bitset<448> bit_mes448;
	for(int i=0;i<size*8;i++){
		bit_mes448[448-size*8+i]=bit_mes[i];
	}
	// cout<<bit_mes448<<endl;
	bit_mes448[448-size*8-1]=1;

	// append length
	bitset<64> leng(size*8);
	bitset<512> bit_mes512;
	for(int i=0;i<448;i++){
		bit_mes512[i+64]=bit_mes448[i];
	}
	for(int i=0;i<64;i++){
		bit_mes512[i]=leng[64-i-1];
	}
	// cout<<bit_mes512<<endl;
	
	// initialize buffer
	bitset<32> M[16];
	for(int i=0;i<16;i++){
		bitset<32> tmp;
		for(int j=0;j<32;j++){
			tmp[j]=bit_mes512[i*32+j];
		}
		M[16-i-1]=tmp;
	}
	int t = 16;

	// for(int i=0;i<16;i++){
	// 	printf("0x%x\n", M[i].to_ulong());
	// }

	// cout<<"M[15]   "<<M[15]<<endl;


	bitset<32> M2[16];

	uint8_t bytes[4];
	for(int i=0;i<14;i++){
	    bytes[0] = (uint8_t) M[i].to_ulong();
	    bytes[1] = (uint8_t) (M[i].to_ulong() >> 8);
	    bytes[2] = (uint8_t) (M[i].to_ulong() >> 16);
	    bytes[3] = (uint8_t) (M[i].to_ulong() >> 24);
	    uint32_t tmp=(uint32_t)bytes[3]+(uint32_t)(bytes[2]<<8)+(uint32_t)(bytes[1]<<16)+(uint32_t)(bytes[0]<<24);
	    M2[i]=bitset<32> (tmp);
	}
	// cout<<M[14].to_ulong();
	M2[14]=reverse((uint32_t)M[14].to_ulong());
	M2[15]=reverse((uint32_t)M[15].to_ulong());

	cout<<endl;

// cout<<"-------before parse"<<endl;
// 	for(int i=0;i<16;i++){
// 		cout<<i<< "   "<<M2[i]<<endl;
// 		// printf("0x%x\n", M[i].to_ulong());
// 	}

	uint32_t a, b, c, d,  f, g, temp;
	uint32_t h0, h1, h2, h3;
	h0 = 0x67452301;
	h1 = 0xefcdab89;
	h2 = 0x98badcfe;
	h3 = 0x10325476;

	t=(448+64)/32;
	bitset<32> X[16];
	// starting md5
	for(int i=0;i<t/16;i++){
		for(int j=0;j<16;j++){
			X[j]=M2[i*16+j];
		}


        a = h0;
        b = h1;
        c = h2;
        d = h3;
        // Main loop:
        for(i = 0; i<64; i++) {
            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }
 
            temp = d;
            d = c;
            c = b;
            b = b + shift((a + f + T[i] + uint32_t(M2[g].to_ulong())), s[i]);
            a = temp;
        }

        // Add this chunk's hash to result so far:
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
	}

	cout.setf(ios::hex, ios::basefield);


	bitset<32> M3[4];

	// endian change
    bytes[0] = (uint8_t) h0;
    bytes[1] = (uint8_t) (h0>> 8);
    bytes[2] = (uint8_t) (h0>> 16);
    bytes[3] = (uint8_t) (h0>> 24);
    uint32_t tmp=(uint32_t)bytes[3]+(uint32_t)(bytes[2]<<8)+(uint32_t)(bytes[1]<<16)+(uint32_t)(bytes[0]<<24);
    M3[0]=bitset<32> (tmp);
    // cout<<M3[0].to_ulong()<<endl;
    bytes[0] = (uint8_t) h1;
    bytes[1] = (uint8_t) (h1>> 8);
    bytes[2] = (uint8_t) (h1>> 16);
    bytes[3] = (uint8_t) (h1>> 24);
	tmp=(uint32_t)bytes[3]+(uint32_t)(bytes[2]<<8)+(uint32_t)(bytes[1]<<16)+(uint32_t)(bytes[0]<<24);
    M3[1]=bitset<32> (tmp);
    // cout<<M3[1].to_ulong()<<endl;
    bytes[0] = (uint8_t) h2;
    bytes[1] = (uint8_t) (h2>> 8);
    bytes[2] = (uint8_t) (h2>> 16);
    bytes[3] = (uint8_t) (h2>> 24);
	tmp=(uint32_t)bytes[3]+(uint32_t)(bytes[2]<<8)+(uint32_t)(bytes[1]<<16)+(uint32_t)(bytes[0]<<24);
    M3[2]=bitset<32> (tmp);
    // cout<<M3[2].to_ulong()<<endl;
    bytes[0] = (uint8_t) h3;
    bytes[1] = (uint8_t) (h3>> 8);
    bytes[2] = (uint8_t) (h3>> 16);
    bytes[3] = (uint8_t) (h3>> 24);
	tmp=(uint32_t)bytes[3]+(uint32_t)(bytes[2]<<8)+(uint32_t)(bytes[1]<<16)+(uint32_t)(bytes[0]<<24);
    M3[3]=bitset<32> (tmp);
	    // cout<<M3[3].to_ulong()<<endl;

	// cout<<h0<<endl;
	// cout<<h1<<endl;
	// cout<<h2<<endl;
	// cout<<h3<<endl;
	cout<<"md5 code is: "<<endl;
	cout<<M3[0].to_ulong();
	cout<<M3[1].to_ulong();
	cout<<M3[2].to_ulong();
	cout<<M3[3].to_ulong()<<endl;




	return 0;
}

