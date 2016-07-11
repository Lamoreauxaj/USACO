/*
ID: lamorea1
LANG: C++11
PROG: comehome
*/
#include <cstdio>
#include <queue>
#include <cctype>
using namespace std;

#define NODES 150
const int inf = 1000000000;

vector<vector<pair<int,int> > > adjList(NODES);
vector<int> shortest(NODES,inf);

void dijkstra(int origin) { //SSSP
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	shortest[origin] = 0; pq.push(pair<int,int>(0,origin));
	while(!pq.empty()) {
		pair<int,int> v = pq.top(); pq.pop();
		if(v.first > shortest[v.second]) continue; //don't process worse distances
		for(int i = 0; i < adjList[v.second].size(); i++) { //for all neighbors
			pair<int,int> u = adjList[v.second][i];
			if(shortest[v.second]+u.second<shortest[u.first]) {//if going through the current node to this neighbor is better than current
				shortest[u.first] = shortest[v.second]+u.second;
				pq.push(pair<int,int>(shortest[u.first],u.first)); //add it to the pq
			}
		}
	}
}

int main() {
	freopen("comehome.in","r",stdin);
	freopen("comehome.out","w",stdout);

	//take input
	int n; scanf("%d",&n); char a, b; int d;
	for(int i = 0; i < n; i++) {
		scanf(" %c %c %d",&a,&b,&d);
		adjList[a].push_back(pair<int,int>(b,d));
		adjList[b].push_back(pair<int,int>(a,d));
	}

	//find the closest one to 'Z' after calling dijkstra
	dijkstra('Z');
	int mini = inf;
	char closest = '!';
	for(int i = 0; i < shortest.size(); i++) {
		if(i=='Z'||!isupper(i)) continue; //cows only exist on upper case barns
		if(shortest[i]<mini) {
			mini = shortest[i];
			closest = i;
		}
	}

	printf("%c %d\n",closest,mini);

	return 0;
}
