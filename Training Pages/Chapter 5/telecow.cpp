/*
ID: lamorea1
LANG: C++11
PROG: telecow
*/
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int N, M, s, e;
int res[200][200];

int mflow() {
	//copy res array
	int r[200][200];
	for(int i = 0; i < 2*N; i++) for(int c = 0; c < 2*N; c++) r[i][c] = res[i][c];
	int mf = 0;
	bool visited[200]; int parent[200]; queue<int> q;
	while(1) {
		//run bfs
		fill(visited,visited+N+N,false); fill(parent,parent+N+N,-1); q = queue<int>();
		q.push(s); visited[s] = true;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(u==e+N) break;
			for(int i = 0; i < 2*N; i++) {
				if(!visited[i] && r[u][i] > 0) {
					visited[i] = true;
					q.push(i);
					parent[i] = u;
				}
			}
		}
		//augment
		int pos = e+N;
		int f = 2000000000;
		while(parent[pos]!=-1) {
			f = min(f,r[parent[pos]][pos]);
			pos = parent[pos];
		}
		if(pos!=s) break;
		pos = e+N;
		while(parent[pos]!=-1) {
			r[parent[pos]][pos] -= f;
			r[pos][parent[pos]] += f;
			pos = parent[pos];
		}
		mf += f;
	}
	return mf;
}

int main() {
	freopen("telecow.in","r",stdin);
	freopen("telecow.out","w",stdout);

	//input
	scanf("%d %d %d %d",&N,&M,&s,&e); s-=1; e-=1;
	fill(&res[0][0],&res[0][0]+4*N*N,0); int a, b;
	for(int i = 0; i < N; i++) res[i][i+N] = res[i+N][i] = 1; //replace each vertex with an edge that goes to itself (split each vertex into in and out so we can preform mincut on edges)
	for(int i = 0; i < M; i++) { scanf("%d %d",&a,&b); a-=1; b-=1;
		res[a][b+N] += 1;
		res[b][a+N] += 1;
	}

	//figure out which vertices reduce the max flow
	int mf = mflow();
	vector<int> ans;
	for(int i = 0; i < N&&mf > 0; i++) {if(i==s||i==e) continue;
		res[i][i+N] = res[i+N][i] = 0;
		int f = mflow();
		if(f < mf) mf = f, ans.push_back(i+1);
		else res[i][i+N] = res[i+N][i] = 10000;
	}

	//output
	printf("%d\n",(int)ans.size());
	printf("%d",ans[0]);
	for(int i = 1; i < ans.size(); i++) printf(" %d",ans[i]);
	printf("\n");

	return 0;
}
