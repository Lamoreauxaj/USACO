/*
ID: lamorea1
LANG: C++11
PROG: race3
*/
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

vector<int> adjList[50];
bool reachable[50];
bool reachable2[50];
int N;

void bfs(int s, int ignore, bool reachable[50]) { //finds all reachable points from start without using ignore
	fill(reachable,reachable+N,false);
	queue<int> q;
	q.push(s); reachable[s] = true;
	while(!q.empty()) {
		int t = q.front(); q.pop();
		for(int i = 0; i < adjList[t].size(); i++) {
			if(adjList[t][i]!=ignore&&!reachable[adjList[t][i]])
				q.push(adjList[t][i]), reachable[adjList[t][i]] = true;
		}
	}
}

int main() {
	freopen("race3.in","r",stdin);
	freopen("race3.out","w",stdout);

	//input
	int t; int i = 0;
 	while(scanf("%d",&t)&&t!=-1) {
 		while(t!=-2) {
 			adjList[i].push_back(t);
 			scanf("%d",&t);
 		}
 		i++;
	}
	N = i;

	//calculate unavoidable and splitting
	vector<int> unavoidable;
	vector<int> splitting;

	for(int i = 1; i < N-1; i++) { //ignore start and end points
		bfs(0,i,reachable); //find all reachables points from start without using i
		if(!reachable[N-1]) unavoidable.push_back(i);
		bool splitt = true; //all splitting are unavoidable but not all unavoidable are splitting
		//check if from i you can traverse back to nodes reachable without i (not splitting as graphs overlap)
		bfs(i,-1,reachable2);
		for(int i = 0; i < N; i++) if(reachable2[i]&&reachable[i]) splitt = false; //check if i onwards and start towards i share any nodes
		if(splitt) splitting.push_back(i);
	}

	//output
	printf("%d",(int)unavoidable.size()); for(int i = 0; i < unavoidable.size(); i++) printf(" %d",unavoidable[i]); printf("\n");
	printf("%d",(int)splitting.size()); for(int i = 0; i < splitting.size(); i++) printf(" %d",splitting[i]); printf("\n");

	return 0;
}
