/*
ID: lamorea1
LANG: C++
PROG: palsquare
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char* tostring(int i, int B = 10) {
	char* ret = new char[100];
	int pos = 0;
	while(i>0) {
		ret[pos++] = ((i%B)>=10)?'A'+i%B-10:'0'+i%B;
		i/=B;
	}
	ret[pos] = '\0';
	reverse(ret,ret+pos);
	return ret;
}

bool ispalin(char* num) {
	int i = 0;
	int j = strlen(num)-1;
	while(i<j) {
		if(num[i]!=num[j]) return false;
		i++;
		j--;
	}return true;
}

int main() {
	freopen("palsquare.in","r",stdin);
	freopen("palsquare.out","w",stdout);
	
	int B;
	scanf("%d",&B);
	for(int i = 1; i <= 300; i++) {
		char* num = tostring(i*i,B);
		if(ispalin(num)) {
			printf("%s %s\n",tostring(i,B),num);
		}
	}

	return 0;
}
