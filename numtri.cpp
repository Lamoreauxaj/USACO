/*
ID: lamorea1
LANG: C++
PROG: numtri
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int R;
int tri[1010][1010];
int sum[1010][1010];

int main() {
	freopen("numtri.in","r,",stdin);
	freopen("numtri.out","w",stdout);

	//take input
	scanf("%d",&R);
	for(int r = 0; r < R; r++)
		for(int c = 0; c <= r; c++)
			scanf("%d",&tri[r][c]);
	for(int c = 0; c < R; c++) sum[R-1][c] = tri[R-1][c];

	//process DP bottom up
	for(int r = R-2; r >= 0; r--)
		for(int c = 0; c <= r; c++)
			sum[r][c] = max(sum[r+1][c],sum[r+1][c+1])+tri[r][c];

	printf("%d\n",sum[0][0]);

	return 0;
}
