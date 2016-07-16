/*
ID: lamroea1
LANG: C++11
PROG: milk6
*/
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int N, M;
int res[32][32];

int mflow(int s, int t, int r[32][32]) { //returns max flow from s --> t in graph r
	int res[32][32];
	for(int i = 0; i < 32; i++) for(int j = 0; j < 32; j++) res[i][j] = r[i][j];
	int mf = 0; int f;
	bool visited[32]; int parent[32]; queue<int> q;
	while(1) {
		//run bfs
		fill(visited,visited+N,false); fill(parent,parent+32,-1); q = queue<int>();
		q.push(s); visited[s] = true;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(u==t) break;
			for(int i = 0; i < N; i++) {
				if(res[u][i] > 0 && !visited[i]) {
					visited[i] = true;
					parent[i] = u;
					q.push(i);
				}
			}
		}
		//augment path
		f = 1000000000;
		int pos = t;
		while(parent[pos]!=-1) {
			f = min(f,res[parent[pos]][pos]);
			pos = parent[pos];
		}
		if(pos!=s) break;
		pos = t;
		while(parent[pos]!=-1) {
			res[parent[pos]][pos] -= f;
			res[pos][parent[pos]] += f;
			pos = parent[pos];
		}
		mf += f;
	}
	return mf;
}

int main() {
	freopen("milk6.in","r",stdin);
	freopen("milk6.out","w",stdout);

	//input
	fill(&res[0][0],&res[0][0]+1024, 0);
	scanf("%d %d",&N,&M); int a, b, d;
	vector<pair<int,pair<int,pair<int,int>>>> edges;
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d",&a,&b,&d);
		res[a-1][b-1] += d;
		edges.push_back(pair<int,pair<int,pair<int,int>>>(-d,pair<int,pair<int,int>>(i,pair<int,int>(a-1,b-1))));
	}

	//find min cut edges
	sort(edges.begin(),edges.end());
	int total = 0; vector<int> mincut;
	int mf = mflow(0,N-1,res);
	for(int i = 0; i < M; i++) {
		d = -edges[i].first;
		int j = edges[i].second.first;
		a = edges[i].second.second.first;
		b = edges[i].second.second.second;
		res[a][b] -= d;
		int f = mflow(0,N-1,res);
		if(mf-f == d) {
			total += d;
			mincut.push_back(j);
			mf = f;
		}else res[a][b] += d;
	}

	//output
	sort(mincut.begin(),mincut.end());
	printf("%d %d\n",total,int(mincut.size()));
	for(int i = 0; i < mincut.size(); i++) printf("%d\n",mincut[i]+1);

 	return 0;
}
