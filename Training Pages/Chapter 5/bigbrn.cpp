/*
ID: lamorea1
LANG: C++11
PROG: bigbrn
*/
#include <cstdio>
#include <algorithm>
using namespace std;

bool tree[1000][1000];
int best[1000][1000];
int N, T;

bool canexpand(int r, int c, int sz) {
	if(r+sz>=N || c+sz>=N) return false;
	for(int rr = r; rr <= r+sz; rr++) if(tree[rr][c+sz]) return false;
	for(int cc = c; cc <= c+sz; cc++) if(tree[r+sz][cc]) return false;
	return true;
}

int main() {
	freopen("bigbrn.in","r",stdin);
	freopen("bigbrn.out","w",stdout);

	//input
	scanf("%d %d",&N,&T); int a, b;
	for(int i = 0; i < T&&scanf("%d %d",&a,&b); i++) tree[a-1][b-1] = true;

	//fill best array
	int ans = 0;
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) {if(tree[r][c]) continue;
			int sz = (c==0)?max(1,best[max(r-1,0)][c]-1):(max(1,best[r][c-1]-1));
			while(canexpand(r,c,sz)) sz++;
			best[r][c] = sz;
			ans = max(ans,best[r][c]);
		}
	}

	//output
	printf("%d\n",ans);

	return 0;
}
