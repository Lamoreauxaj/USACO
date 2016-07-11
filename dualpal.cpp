/*
ID: lamorea1
LANG: C++
PROG: dualpal
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char* tostring(int i, int B = 10) {
	char* ret = new char[100];
	int pos = 0;
	while(i>0) {
		ret[pos++] = (i%B)>=10?'A'+i%B-10:'0'+i%B;
		i/=B;
	}
	ret[pos] = '\0';
	reverse(ret,ret+pos);
	return ret;
}

bool ispalin(char* str) {
	int i = 0;
	int j = strlen(str)-1;
	while(i<j) {
		if(str[i]!=str[j]) return false;
		i++; j--;
	}return true;
}

int main() {
	freopen("dualpal.in","r",stdin);
	freopen("dualpal.out","w",stdout);

	int N, S;
	scanf("%d %d\n",&N,&S);

	for(int i = S+1; N; i++) {
		int count = 0;
		for(int B = 2; B <= 10&&count<2; B++) {
			if(ispalin(tostring(i,B))) count++;
		}
		if(count==2) {
			printf("%d\n",i);
			N--;
		}
	}

	return 0;
}
