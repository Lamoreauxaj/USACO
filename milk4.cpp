/*
ID: lamorea1
LANG: C++11
PROG: milk4
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int Q, N;
int val[10000];
bool best[10000];
int best_size;

bool sol[10000];
int vol, sol_size, pos;
vector<bool> can;
bool dfsbound(int bound) { //dfs with a set depth
	if(sol_size == bound) {
		if(can[Q]) {
			return true;
		}
		return false;
	}
	for(int i = pos; i < N; i++) {
		bool tmp = sol[i];
		sol[i] = true;
		if(!tmp) sol_size++;
		int tpos = pos; pos = i+1;
		vector<int> temp;
		for(int j = 0; j+val[i] <= Q; j++) if(can[j]&&!can[j+val[i]]) can[j+val[i]] = true, temp.push_back(j+val[i]); //mark out numbers that are now reachable
		if(dfsbound(bound)) return true;
		for(int i = 0; i < temp.size(); i++) can[temp[i]] = false;
		pos = tpos;
		if(!tmp) sol_size--;
		sol[i] = tmp;
	}return false;
}

int main() {
	freopen("milk4.in","r",stdin);
	freopen("milk4.out","w",stdout);

	//input
	scanf("%d %d",&Q,&N);
	for(int i = 0; i < N; i++) scanf("%d",&val[i]);
	sort(val,val+N);

	//run dfs with interitive deepening
	sol_size = 0; vol = 0; pos = 0; can = vector<bool>(Q+1,false); can[0] = true;
	for(int i = 1; i <= N; i++) {
		if(dfsbound(i)) break;
	}

	//output
	printf("%d",sol_size);
	for(int i = 0; i < N; i++) if(sol[i]) printf(" %d",val[i]); printf("\n");

	return 0;
}
