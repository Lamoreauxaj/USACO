/*
ID: lamorea1
LANG: C++11
PROG: range
*/
#include <cstdio>
#include <map>
using namespace std;

int N;
bool field[255][255];
map<int,int> freq;
int good[255][255];

bool inbounds(int r, int c) {
	return r>=0&&c>=0&&r<N&&c<N;
}

//check if a square starting at r,c with a current size size can be made one bigger by extending the east and south sides
bool canextend(int r, int c, int size) {
	for(int rr = r; rr <= r+size; rr++) if(!inbounds(rr,c+size)||!field[rr][c+size]) return false;
	for(int cc = c; cc <= c+size; cc++) if(!inbounds(r+size,cc)||!field[r+size][cc]) return false;
	return true;
}

int main() {
	freopen("range.in","r",stdin);
	freopen("range.out","w",stdout);

	//input
	scanf("%d",&N);
	char t[255];
	for(int r = 0; r < N&&scanf("%s",t); r++) for(int c = 0; c < N; c++) field[r][c] = t[c]=='1';

	//fill good array
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) { if(!field[r][c]) continue;
			int sz = 1;
			if(c>0) sz = good[r][c-1]-1;
			while(canextend(r,c,sz)) {
				sz++;
			}
			good[r][c] = sz;
		}
	}

	//fill freq map
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) {
			for(int sz = 2; sz <= good[r][c]; sz++) {
				freq[sz]++;
			}
		}
	}

	//output
	for(pair<int,int> tmp : freq) {
		printf("%d %d\n",tmp.first,tmp.second);
	}

	return 0;
}
