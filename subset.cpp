/*
ID: lamorea1
LANG: C++
PROG: subset
*/
#include <cstdio>
using namespace std;

int N, total, half;

long long memo[800][45];

//fill memo with -1
void init() {
	for(int i = 0; i < 800; i++) for(int j = 0; j < 45; j++) memo[i][j] = -1;
}

//recursively try all possible subsets of n
long long recurse(int sum, int pos) { //recursive approach with memoization
	if(memo[sum][pos]!=-1) return memo[sum][pos];
	if(pos==0) {
		if(sum==half) return memo[sum][pos] = 1LL;
		else return 0LL;
	}
	if(sum>half) return 0LL;
	return memo[sum][pos] = recurse(sum+pos,pos-1) + recurse(sum,pos-1);
}

int main() {
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);

	//take input
	scanf("%d",&N);
	total = (N+1)*N/2;
	if(total%2!=0) printf("0\n"); //can't be split into halves
	else {
		half = total/2;
		init();
		printf("%lld\n",recurse(0,N)/2);
	}

	return 0;
}
