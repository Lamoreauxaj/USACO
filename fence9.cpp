/*
ID: lamorea1
LANG: C++11
PROG: fence9
*/
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
using namespace std;

int n, m, p;

int main() {
	freopen("fence9.in","r",stdin);
	freopen("fence9.out","w",stdout);

	//input
	scanf("%d %d %d",&n,&m,&p);

	//count lattice points within triangle
	int count = 0;
	for(int y = 1; y < m; y++) {
		int left = y*n/m;
		int right = ceil(p - y*(p-n) / double(m));
		count+=right-left-1;
	}

	//output
	printf("%d\n",count);

	return 0;
}
