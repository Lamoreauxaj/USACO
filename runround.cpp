/*
ID: lamorea1
LANG: C++
PROG: runround
*/
#include <cstdio>
#include <cstring>
using namespace std;

//returns whether n contains only 1-9 at most once and no zeroes
bool isunique(char* n) {
	int seen = 0;
	for(int i = 0; i < strlen(n); i++) {
		if(n[i]=='0') return false;
		if(seen&(1<<(n[i]-'1'))) return false;
		seen|=(1<<(n[i]-'1'));
	}
	return true;
}

//returns whether a number is a runround number
bool isrunround(char* n) {
	int pos = 0;
	int visited = 0;
	while(true) {
		if(visited&(1<<pos)) break;
		visited|=(1<<pos);
		pos+=n[pos]-'0';
		pos%=strlen(n);
	}
	return pos==0&&((visited&((1<<strlen(n))-1))==((1<<strlen(n))-1)); //back at start and all numbers touched
}

long long M;

int main() {
	freopen("runround.in","r",stdin);
	freopen("runround.out","w",stdout);

	scanf("%lld",&M);
	char* num_str = new char[15];
	for(long long num = M+1; ; num++) { //find next highest runround
		sprintf(num_str,"%lld",num);
		if(isunique(num_str)&&isrunround(num_str)) {
			printf("%s\n",num_str);
			break;
		}
	}

	return 0;
}
