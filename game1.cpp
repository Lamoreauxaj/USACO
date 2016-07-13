/*
ID: lamorea1
LANG: C++11
PROG: game1
*/
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 105

int N;
int nums[MAXN];
pair<int,int> memo[MAXN][MAXN];
pair<int,int> score(int s, int e) {
	if(memo[s][e]!=pair<int,int>(-1,-1)) return memo[s][e]; //if already found
	if(s>e) return pair<int,int>(0,0); //base case of no items; neither player gets points
	bool player1 = ( N - (s-e+1) ) % 2 == 0;
	if(player1) {//if its player1's turn
		pair<int,int> ret = score(s+1,e); ret.first += nums[s];
		if(score(s,e-1).first + nums[e] > ret.first) { //if this gives player1 more points
			ret = score(s,e-1);
			ret.first += nums[e];
		}else if(score(s,e-1).first + nums[e] == ret.first) {
			if(score(s,e-1).second < ret.second) { //if this denies player2 more points
				ret = score(s,e-1);
				ret.first += nums[e];
			}
		}
		return memo[s][e] = ret;
	}else { //if its player2's turn
		pair<int,int> ret = score(s+1,e); ret.second += nums[s];
		if(score(s,e-1).second + nums[e] > ret.second) { //if this gives player2 more points
			ret = score(s,e-1);
			ret.second += nums[e];
		}else if(score(s,e-1).second + nums[e] == ret.second) {
			if(score(s,e-1).first < ret.first) { //if this denies player1 more points
				ret = score(s,e-1);
				ret.second += nums[e];
			}
		}
		return memo[s][e] = ret;
	}
}

int main() {
	freopen("game1.in","r",stdin);
	freopen("game1.out","w",stdout);

	//input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) scanf("%d",&nums[i]);
	fill(&memo[0][0],&memo[0][0]+MAXN*MAXN,pair<int,int>(-1,-1));


	//output
	printf("%d %d\n",score(0,N-1).first,score(0,N-1).second);

	return 0;
}
