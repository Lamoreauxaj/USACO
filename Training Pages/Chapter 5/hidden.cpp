/*
ID: lamorea1
LANG: C++11
PROG: hidden
*/
#include <cstdio>
#include <string>
using namespace std;

int L;
string S;
int best;

//returns true if i is lexiographically less than j
int comp(int i, int j) {
	for(int k = 0; k < L; k++,i++,j++) {
		if(i>=L) i-=L; if(j>=L) j-=L;
		if(S[i] < S[j]) return -1;
		if(S[i] != S[j]) return 1;
	}
	return 0;
}

int main() {
	freopen("hidden.in","r",stdin);
	freopen("hidden.out","w",stdout);

	//input
	scanf("%d",&L); char temp[100];
	while(scanf("%s",temp)!=EOF) {
		S += temp;
	}

	//process
	best = 0;
	for(int i = 1; i < L; i++) {
		if(S[i] == S[i-1]) continue; //optimization because these cases are always lexiographically worse
		if(i > 2 && S[i] == S[i-2] && S[i-1] == S[i-3]) continue;
		int t = comp(i,best);
		if(t==-1) best = i;
	}

	//output
	printf("%d\n",best);

	return 0;
}
