/*
ID: lamorea1
LANG: C++11
PROG: stamps
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N, K;
int val;
int coin[2000000];

int main() {
	freopen("stamps.in","r",stdin);
	freopen("stamps.out","w",stdout);

	//take input
	scanf("%d %d",&K,&N);

	coin[0] = 0;
	for(int i = 1; i < 2000000; i++) coin[i] = 1000000000;

	//preform coin change
	for(int i = 0; i < N&&scanf("%d",&val); i++)
		for(int j = val; j < 2000000; j++)
			coin[j] = min(coin[j],coin[j-val]+1);

	//print output
	for(int i = 0; i < 2000000; i++) {
		if(coin[i]>K) {
			printf("%d\n",i-1);
			break;
		}
	}

	return 0;
}
