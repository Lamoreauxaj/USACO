/*
ID: lamorea1
LANG: C++11
PROG: ditch
*/
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int res[200][200];
int N, M;

int karp(int s, int e) { //returns maxflow
	int mf = 0;
	bool visited[200];  int parent[200];  queue<int> q;
	while(true) {
		//run bfs
		fill(parent,parent+M,-1); fill(visited,visited+M,false); q = queue<int>(); //reset bfs variables
		q.push(s); visited[s] = true;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(u==e) break;
			for(int i = 0; i < M; i++) {
				if(res[u][i] > 0 && !visited[i]) {
					visited[i] = true;
					q.push(i);
					parent[i] = u;
				}
			}
		}
		int f = 1000000000;
		//find the min edge on the path
		int pos = e;
		while(parent[pos]!=-1) {
			f = min(f,res[parent[pos]][pos]);
			pos = parent[pos];
		}
		if(pos!=s) break; //no path was found (didn't make it to start)
		//decrement the path and increment the reverse of the path
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
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);

	//input
	scanf("%d %d",&N,&M);
	fill(&res[0][0],&res[0][0]+M*M, 0); int a, b, d;
	for(int i = 0; i < N; i++) {
		scanf("%d %d %d",&a,&b,&d); a-=1; b-=1;
		// res[a][b] = d;
		res[a][b] += d;
	}

	//output
	printf("%d\n",karp(0,M-1));

	return 0;
}
