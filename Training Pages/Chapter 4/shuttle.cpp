/*
ID: lamorea1
LANG: C++11
PROG: shuttle
*/
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

string goal;
int N;

string state;
int sol[1000];
int sol_size;

bool dfs(int space) {
	if(state==goal) return true;

	if(space > 1 && state[space-2] == 'W') {
		sol[sol_size] = space-2;
		sol_size++;
		state[space-2] = ' '; state[space] = 'W';
		if(dfs(space-2)) return true;
		state[space] = ' '; state[space-2] = 'W';
		sol_size--;
	}
	if(space > 0 && state[space-1] == 'W') {
		sol[sol_size] = space-1;
		sol_size++;
		state[space-1] = ' '; state[space] = 'W';
		if(dfs(space-1)) return true;
		state[space] = ' '; state[space-1] = 'W';
		sol_size--;
	}
	if(space < N-1 && state[space+1] == 'B') {
		sol[sol_size] = space+1;
		sol_size++;
		state[space+1] = ' '; state[space] = 'B';
		if(dfs(space+1)) return true;
		state[space] = ' '; state[space+1] = 'B';
		sol_size--;
	}
	if(space < N-2 && state[space+2] == 'B') {
		sol[sol_size] = space+2;
		sol_size++;
		state[space+2] = ' '; state[space] = 'B';
		if(dfs(space+2)) return true;
		state[space] = ' '; state[space+2] = 'B';
		sol_size--;
	}
	return false;
}

int main() {
	freopen("shuttle.in","r",stdin);
	freopen("shuttle.out","w",stdout);

	//input
	scanf("%d",&N);
	state = string(N,'W') + " " + string(N,'B');
	goal = string(N,'B') + " " + string(N,'W');
	N = N*2 + 1;

	//output
	sol_size = 0;
	dfs(N/2);

	for(int i = 0; i < sol_size; i++) {
		if(i%20!=0) printf(" ");
		printf("%d",sol[i]+1);
		if(i==sol_size-1||i%20==19) printf("\n");
	}
	

	return 0;
}
