/*
ID: lamorea1
LANG: C++11
PROG: inflate
*/
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

int val, wt;
int knapsack[10010];
int M, N;

int main() {
	freopen("inflate.in","r",stdin);
	freopen("inflate.out","w",stdout);

	//take input
	scanf("%d %d",&M,&N);

	//run knapsack
	fill(knapsack,knapsack+10010,0);
	for(int i = 0; i < N&&scanf("%d %d",&val,&wt); i++)
		for(int j = wt; j <= M; j++)
			knapsack[j] = max(knapsack[j],knapsack[j-wt]+val);

	printf("%d\n",knapsack[M]);//print output

	return 0;
}
