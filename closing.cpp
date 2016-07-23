/*
ID: lamorea1
LANG: C++11
PROG: closing
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> adjList[3000];
int order[3000]; //stores the numbers that will be removed from the graph
int place[3000]; //stores when this number is removed from the graph

class UnionFind {
private:
	vector<int> p, rank;
public:
	UnionFind(int N) {rank.assign(N,0); p.assign(N,0); for(int i = 0; i < N; i++) p[i] = i;}
	int findSet(int i) {return (p[i]==i)?i:(p[i] = findSet(p[i]));}
	bool sameSet(int i, int j) {return findSet(i) == findSet(j);}
	bool unionSet(int i, int j) {
		if(!sameSet(i,j)) {
			int x = findSet(i); int y = findSet(j);
			if(rank[x] > rank[y]) p[y] = x;
			else {p[x] = y; if(rank[x]==rank[y]) rank[y]++;}
			return true;
		}return false;
	}
};

int main() {
	freopen("closing.in","r",stdin);
	freopen("closing.out","w",stdout);

	//input
	scanf("%d %d",&N,&M); int a, b;
	vector<pair<int,int>> edges; //temporarily store the edges before adding them to the grpah
	for(int i = 0; i < M; i++) {
		scanf("%d %d",&a,&b); a-=1; b-=1;
		edges.push_back(pair<int,int>(a,b));
	}
	for(int i = 0; i < N; i++) {
		scanf("%d",&a); a-=1;
		order[i] = a;
		place[a] = i;
	}

	//make sure adjList only stores vertices that come before it in the list
	for(int i = 0; i < edges.size(); i++) {
		pair<int,int> edge = edges[i];
		if(place[edge.first] > place[edge.second]) adjList[edge.second].push_back(edge.first);
		else adjList[edge.first].push_back(edge.second);
	}


	UnionFind uf(N);
	int num_comps = 0; //keep number of comps
	bool res[3000]; //store answers
	//add vertices one by one in reverse
	for(int i = N-1; i >= 0; i--) {
		num_comps++; //add a new vertice
		for(int j = 0; j < adjList[order[i]].size(); j++) if(uf.unionSet(order[i],adjList[order[i]][j])) { num_comps--; } //union it with it's neighbors
		res[i] = num_comps==1;
	}

	//output
	for(int i = 0; i < N; i++) if(res[i]) printf("YES\n"); else printf("NO\n");

	return 0;
}
