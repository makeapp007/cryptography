#include <iostream>
#include <vector>
using namespace std;

char key[16]={"hello rc4"};
int S[256];

vector<int> Init(char key[16], int S[256]){
	int i=0,j=0;
	vector<int> state;
	for(int i=0;i<256;i++){
		S[i]=i;
		key[i]=key[i%16];
	}
	j=0;
	for(int i=0;i<256;i++){
		j=j+S[i]+S[j];
		int tmp=S[i];
		S[i]=S[j];
		S[j]=tmp;
	}
	i=0;j=0;
	state.push_back(i);
	state.push_back(j);
}

vector<int> GetBits(int S[256],int i,int j){
	vector<int> state;
	i=i+1;
	j=j+S[i];
	int tmp=S[i];
	S[i]=S[j];
	S[j]=tmp;
	int t=S[i]+S[j];
	int y=S[t];
	state.push_back(y);
	state.push_back(i);
	state.push_back(j);

}

int main(){
	cout<<"hello rc4"<<endl;


	return 0;
}




