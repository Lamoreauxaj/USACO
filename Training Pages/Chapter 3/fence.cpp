/*
ID: lamorea1
LANG: C++11
PROG: fence
*/
#include <cstdio>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;
const int NODES = 500;

int E;
vector<pair<int,int>> adjList[NODES]; //sorted vectors so first path is correct path
list<int> cyc;

//first finds a complete tour and then recursively fills in edges not used
void EulerPath(list<int>::iterator i, int u) { //vector or list doesn't really matter we use list
	list<int>::iterator pass = cyc.insert(next(i),u); //for easy insertions in the middle
	for (int j = 0; j < adjList[u].size(); j++) { //find an edge not taken
		if (adjList[u][j].second) {
			adjList[u][j].second = 0; //delete edge
			for(int k = 0; k < adjList[adjList[u][j].first].size(); k++) {
				if (adjList[adjList[u][j].first][k].first == u && adjList[adjList[u][j].first][k].second) {
					adjList[adjList[u][j].first][k].second = 0;//delete edge both ways
					break;
				}
			}
			EulerPath(pass,adjList[u][j].first); //recurse
		}	
	}
}

int main() {
	freopen("fence.in","r",stdin);
	freopen("fence.out","w",stdout);

	//input
	scanf("%d",&E); int a,b;
	for(int i = 0; i < E; i++) {
		scanf("%d %d",&a,&b); a-=1; b-=1;
		adjList[a].push_back(pair<int,int>(b,1));
		adjList[b].push_back(pair<int,int>(a,1));
	}

	//sort adjList
	for(int i = 0; i < NODES; i++) sort(adjList[i].begin(),adjList[i].end());

	//call EulerPath on first node of odd degree or first node if none
	int i;
	for(i = 0; i < NODES; i++) if(adjList[i].size()%2!=0) {
		EulerPath(cyc.begin(),i); break;
	}
	if(i==NODES)
		for(i = 0; i < NODES; i++) if(adjList[i].size()>0) {
			EulerPath(cyc.begin(),i);
			break;
		}
	
	//output
	for(int j : cyc) printf("%d\n",j+1);
	return 0;
}
