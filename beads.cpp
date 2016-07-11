/*
ID: lamorea1
LANG: C++
PROG: beads
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
char necklace[720];

bool eq(int i, int j) {
	i%=N; j%=N;
	if(necklace[i]=='w'||necklace[j]=='w') return true;
	return necklace[i]==necklace[j];
}

int compute(int start) {
	int pos = start+1;
	int last = start;
	while(pos<2*N&&eq(pos,last)) {
		if(necklace[last%N]=='w') last = pos;
		pos++;
	}
	last = pos;
	pos++;
	while(pos<2*N&&eq(pos,last)) {
		if(necklace[last%N]=='w') last = pos;
		pos++;
	}
	return pos-start;
}

int main() {
	freopen("beads.in","r",stdin);
	freopen("beads.out","w",stdout);

	scanf("%d",&N);
	scanf("%s",necklace);

	int m = 0;
	for(int i = 0; i < 2*N; i++) {
		m = max(m,compute(i));
	}

	printf("%d\n",min(m,N));

	return 0;
}
