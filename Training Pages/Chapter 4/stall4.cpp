/*
ID: lamorea1
LANG: C++11
PROG: stall4
*/
#include <cstdio>
#include <queue>
using namespace std;

int res[402][402]; //node 0 is source; 1-200 are the stalls; 201-400 are the cows; 401 is the sink
int N, M;

int karp(int s, int e) {
	int mf = 0;
	bool visited[402]; int parent[402]; queue<int> q;
	while(1) {
		//run bfs
		fill(visited,visited+402,false); fill(parent,parent+402,-1); q = queue<int>();
		q.push(s); visited[s] = true;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(u==e) break;
			for(int i = 0; i < 402; i++) {
				if(res[u][i] > 0 && !visited[i]) {
					visited[i] = true;
					q.push(i);
					parent[i] = u;
				}
			}
		}
		//find min on path
		int f = 1000000000;
		int pos = e;
		while(parent[pos]!=-1) {
			f = min(f,res[parent[pos]][pos]);
			pos = parent[pos];
		}
		if(pos!=s) break;
		//fix path
		pos = e;
		while(parent[pos]!=-1) {
			res[parent[pos]][pos] -= f;
			res[pos][parent[pos]] += f;
			pos = parent[pos];
		}
		mf+=f;
	}
	return mf;
}

int main() {
	freopen("stall4.in","r",stdin);
	freopen("stall4.out","w",stdout);

	//input
	scanf("%d %d",&N,&M);
	fill(&res[0][0],&res[0][0]+402*402,0);
	for(int i = 0; i < N; i++) {
		int n; scanf("%d",&n);
		for(int j = 0; j < n; j++) {
			int t; scanf("%d",&t);
			res[i+201][t] = 1;
		}
	}
	//init res array for added source and sink
	for(int i = 201; i < 401; i++) {
		res[0][i] = 1;
	}
	for(int i = 1; i < 201; i++) {
		res[i][401] = 1;
	}

	//output
	printf("%d\n",karp(0,401));

	return 0;
}
