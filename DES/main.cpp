#include <iostream>
#include <bitset>
using namespace std;

int main(){
	bitset<6> tmp= 0b110101;
	bitset<6> tmp2= 0b100100;

	// cout<<tmp<<endl;
	// cout<<(tmp<<1)<<endl;
	// cout<<(tmp<<2)<<endl;
	cout<<(tmp ^ tmp2)<<endl;
	// std::bitset<4> foo (std::string("1001"));
 //  std::bitset<4> bar (std::string("0011"));
 //  std::cout << (foo^bar) << '\n';        // 0101

	cout<<(tmp ^ (bitset<6>)0b10)<<endl;

	cout<<"hello world"<<endl;

	cout<<tmp.to_ulong()<<endl;
	bitset<2> row;
	row[1]=tmp[2];
	row[0]=tmp[0];
	cout<<row<<endl;


	bitset<5>	col(tmp.to_string(),0,5);
		cout<<col<<endl;

		int a=4;
		bitset<4> binary(a);
		cout<<binary<<endl;
		// cout<<(a<<1)<<endl;
// Note that &=, |=, and ^= are only defined for bitsets of the same size N.
		bitset<10> a1(110);
		cout<<a1	<<endl;	
		bitset<10> b=0b1111;
		cout<<(a1&b)<<endl;

	bitset<32> R0=(bitset<32>)0b10;
	cout<<R0<<endl;
	cout<<(R0<<32)<<endl;
	// final=(bitset<64>)(R0<<32);

// bit rotate
	bitset<10> a2(0b110);
	cout<<a2<<endl;
cout<<"------------"<<endl;
	cout<<a2[2]<<endl;


char aChar = 97;
cout<<aChar<<endl;
cout<<"------------"<<endl;
	bitset<10> a3(0b110);
	bitset<10> b3(0b111);
	bitset<10> c3(a3.to_ulong()+b3.to_ulong());
	cout<<c3<<endl;

cout<<(a3<<1)<<endl;
cout<<(a3<<0)<<endl;


	return 0;
}
