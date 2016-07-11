/*
ID: lamorea1
LANG: C++11
PROG: agrinet
*/
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int adjMatrix[110][110];
int N;

bool taken[110];
int prims() { //minimum spanning tree
	int cost = 0; fill(taken,taken+N,false); //prevents duplicates on the queue because we just add another copy instead of updating
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	pq.push(pair<int,int>(0,0));
	while(!pq.empty()) { 
		pair<int,int> u = pq.top(); pq.pop(); //take off the vertex closest to the current spanning tree
		if(!taken[u.second]) {
			cost+=u.first;
			taken[u.second] = true;
			for(int i = 0; i < N; i++) { //push on all nearby neighbors
				pq.push(pair<int,int>(adjMatrix[u.second][i],i));
			}
		}
	}
	return cost;
}

int main() {
	freopen("agrinet.in","r",stdin);
	freopen("agrinet.out","w",stdout);

	//take input
	scanf("%d",&N);
	for(int r = 0; r < N; r++) {
		for(int c = 0; c < N; c++) {
			scanf("%d",&adjMatrix[r][c]);
		}
	}

	printf("%d\n",prims());

	return 0;
}
