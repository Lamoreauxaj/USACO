/*
ID: lamorea1
LANG: C++11
PROG: snail
*/
#include <cstdio>
#include <algorithm>
using namespace std;

enum {NORTH, EAST, SOUTH, WEST};

int mod(int a, int m) {
	return (a % m + m) % m;
}

int ans;
int covered;
char map[120][120];
int N, B;

bool inbounds(int r, int c) {return r>=0&&c>=0&&r<N&&c<N;}
void dfs(int r, int c, int dir) {
	map[r][c] = '!';
	covered++;
	int rr = r; int cc = c;
	if(dir==NORTH) rr--; if(dir==EAST) cc++;
	if(dir==SOUTH) rr++; if(dir==WEST) cc--;
	ans = max(ans,covered);
	//if can't travel forward because of barrier
	if(!inbounds(rr,cc)||map[rr][cc]=='#') {
		int newdir = mod(dir+1,4);
		rr = r; cc = c;
		if(newdir==NORTH) rr--; if(newdir==EAST) cc++;
		if(newdir==SOUTH) rr++; if(newdir==WEST) cc--;
		if(inbounds(rr,cc)&&map[rr][cc]=='.')
			dfs(rr,cc,newdir);
		newdir = mod(dir-1,4);
		rr = r; cc = c;
		if(newdir==NORTH) rr--; if(newdir==EAST) cc++;
		if(newdir==SOUTH) rr++; if(newdir==WEST) cc--;
		if(inbounds(rr,cc)&&map[rr][cc]=='.')
			dfs(rr,cc,newdir);
	}else if(inbounds(rr,cc)&&map[rr][cc]=='.') { //if can travel forward
		dfs(rr,cc,dir);
	}
	map[r][c] = '.';
	covered--;
}

int main() {
	freopen("snail.in","r",stdin);
	freopen("snail.out","w",stdout);

	//input
	scanf("%d %d",&N,&B);
	for(int r = 0; r < N; r++) for(int c = 0; c < N; c++) map[r][c] = '.';
	for(int i = 0; i < B; i++) {
		char c; int r;
		scanf(" %c%d",&c,&r);
		map[c-'A'][r-1] = '#';
	}

	//call dfs
	ans = 0;
	covered = 0;
	dfs(0,0,EAST);
	dfs(0,0,SOUTH);

	//output
	printf("%d\n",ans);

	return 0;
}
