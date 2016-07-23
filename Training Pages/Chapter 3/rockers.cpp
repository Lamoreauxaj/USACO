/*
ID: lamorea1
LANG: C++11
PROG: rockers
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N, T, M;
int val[25];
int memo[25][25][25];

int count(int disk, int pos, int cap) {
	if(disk==M) return 0;
	if(pos==N) return 0;
	if(memo[disk][pos][cap]!=-1) return memo[disk][pos][cap];
	if(cap>=val[pos]) return memo[disk][pos][cap] = max(count(disk,pos+1,cap-val[pos])+1,max(count(disk+1,pos,T),count(disk,pos+1,cap)));
	return memo[disk][pos][cap] = max(count(disk+1,pos,T),count(disk,pos+1,cap));
}

int main() {
	freopen("rockers.in","r",stdin);
	freopen("rockers.out","w",stdout);

	//input
	scanf("%d %d %d",&N,&T,&M);
	for(int i = 0; i < N; i++) scanf("%d",&val[i]);
	fill(&memo[0][0][0],&memo[0][0][0]+25*25*25,-1);

	//output
	printf("%d\n",count(0,0,T));

	return 0;
}
