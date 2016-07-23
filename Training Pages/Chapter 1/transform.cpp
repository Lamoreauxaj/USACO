/*
ID: lamorea1
LANG: C++
PROG: transform
*/
#include <cstdio>
using namespace std;

int N;
char map[13][13];
char map1[13][13];

bool eq() {
	for(int r = 0; r < N; r++) for(int c = 0; c < N; c++) if(map[r][c]!=map1[r][c]) return false; return true;
}

void rotate() {
	for(int r = 0; r < (N+1)/2; r++) {
		for(int c = 0; c < N/2; c++) {
			//swap r,c c,n-1-r n-1-r,n-1-c n-1-c,r
			char t = map[r][c];
			map[r][c] = map[N-1-c][r];
			map[N-1-c][r] = map[N-1-r][N-1-c];
			map[N-1-r][N-1-c] = map[c][N-1-r];
			map[c][N-1-r] = t;
		}
	}
}

void reflect() {
	for(int r = 0; r < N; r++) {
		int i = 0;
		int j = N-1;
		while(i<=j) {
			char t = map[r][i];
			map[r][i] = map[r][j];
			map[r][j] = t;
			i++; j--;
		}
	}
}

int main() {
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);

	scanf("%d",&N);
	for(int r = 0; r < N; r++)
		scanf("%s",map[r]);
	for(int r = 0; r < N; r++)
		scanf("%s",map1[r]);

	rotate();
	if(eq()) printf("1");
	else {
		rotate();
		if(eq()) printf("2");
		else {
			rotate();
			if(eq()) printf("3");
			else {
				rotate();
				reflect();
				if(eq()) printf("4");
				else {
					rotate();
					if(eq()) printf("5");
					else {
						rotate();
						if(eq()) printf("5");
						else {
							rotate();
							if(eq()) printf("5");
							else {
								rotate();
								reflect();
								if(eq()) printf("6");
								else printf("7");
							}
						}
					}
				}
			}
		}
	}
	printf("\n");

	return 0;
}
