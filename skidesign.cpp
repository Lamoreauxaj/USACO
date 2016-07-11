/*
ID: lamorea1
LANG: C++
PROG: skidesign
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int N;
int hills[1010];

//returns the price of moving the hills if the range is [start,end]
int cost(int start, int end) {
	int total = 0;
	for(int i = 0; i < N; i++) {
		if(hills[i]<start) total+=pow(start-hills[i],2);
		else if(hills[i]>end) total+=pow(hills[i]-end,2);
	}
	return total;
}

int main() {
	freopen("skidesign.in","r",stdin);
	freopen("skidesign.out","w",stdout);

	//take input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) scanf("%d",&hills[i]);
	sort(hills,hills+N);

	//try all ranges and check which is the mini cost
	int mini = 2147000000;
	for(int start = hills[0]; start+17 <= hills[N-1]; start++) {
		mini = min(cost(start,start+17),mini);
	}

	//print
	if(mini==2147000000) printf("0\n"); //nothing was found (ie already within best range)
	else printf("%d\n",mini);

	return 0;
}
