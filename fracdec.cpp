/*
ID: lamorea1
LANG: C++11
PROG: fracdec
*/
#include <cstdio>
#include <map>
#include <string>
using namespace std;

int main() {
	freopen("fracdec.in","r",stdin);
	freopen("fracdec.out","w",stdout);

	//take input
	int num, den;
	scanf("%d %d",&num,&den);

	//print before decimal
	string output;
	output+=to_string(num/den)+".";
	num%=den;

	//print after decimal place
	map<int,int> past;
	int pos = output.size();
	do {
		num*=10;
		past[num] = pos++;
		output += num/den + '0';
		num = num%den;
	}while(num!=0&&!past.count(num*10));

	if(num!=0&&past.count(num*10))
		output = (output.substr(0,past[num*10])+"("+output.substr(past[num*10])+")");

	for(int i = 0; i < output.size(); i+=76) {
		printf("%s\n",output.substr(i,76).c_str());
	}

	return 0;
}
