/*
ID: lamorea1
LANG: C++11
PROG: schlnet
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> adjList[100];

bool visited[100];
vector<int> S;
int dfs_num[100];
int dfs_low[100];
int dfs_count, num_scc;
int scc_comp[100];

void tarjan(int u) {//find scc's that can be reached from this node
	dfs_num[u] = dfs_low[u] = dfs_count++;;
	visited[u] = true;
	S.push_back(u);
	for(int i = 0; i < adjList[u].size(); i++) {
		int v = adjList[u][i];
		if(dfs_num[v]==-1) tarjan(v);
		if(visited[v]) dfs_low[u] = min(dfs_low[u],dfs_low[v]);
	}

	if(dfs_num[u] == dfs_low[u]) {
		while(1) {
			int v = S.back(); S.pop_back(); visited[v] = false;
			scc_comp[v] = num_scc;
			if(v==u) break;
		}num_scc++;
	}
}

void find_scc() {//find the number of scc's in the graph
	num_scc = 0; fill(visited,visited+N,false); fill(dfs_num,dfs_num+N,-1); fill(dfs_low,dfs_low+N,-1);
	dfs_count = 0;
	for(int i = 0; i < N; i++) {
		if(dfs_num[i]==-1) tarjan(i);
	}
}

int main() {
	freopen("schlnet.in","r",stdin);
	freopen("schlnet.out","w",stdout);

	//input
	scanf("%d",&N); int t;
	for(int i = 0; i < N; i++) {
		while(scanf("%d",&t)&&t) {
			adjList[i].push_back(t-1);
		}
	}

	//find comps and sccs
	find_scc();

	//find the in and out degree of each scc
	int scc_in[100];
	int scc_out[100];
	fill(scc_in,scc_in+num_scc,0);
	fill(scc_out,scc_out+num_scc,0);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < adjList[i].size(); j++) {
			int k = adjList[i][j];
			if(scc_comp[i]!=scc_comp[k]) scc_in[scc_comp[k]]++, scc_out[scc_comp[i]]++;
		}
	}

	//find number of scc's with in and out degree of zero
	int scc_in_zero = 0; //number of scc's with in degree of zero
	int scc_out_zero = 0; //numer of scc's with out degree of zero
	for(int i = 0; i < num_scc; i++) {
		if(scc_in[i]==0) scc_in_zero++;
		if(scc_out[i]==0) scc_out_zero++;
	}

	//output
	printf("%d\n",scc_in_zero); //subtask A
	printf("%d\n",num_scc==1?0:max(scc_in_zero,scc_out_zero)); //subtask B

	return 0;
}
