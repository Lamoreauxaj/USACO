/*
ID: lamorea1
LANG: C++11
PROG: butter
*/
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int inf = 1000000000;

int N, P, C;
int occupied[810]; //stores the number of cows in each pasture
vector<pair<int,int>> adjList[810]; //stores paths
int dist[810][810]; //stores shortest paths
int mini; //minimum path sum

void dijkstras(int s) {//SSSP
	fill(dist[s],dist[s]+810, inf);
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	dist[s][s] = 0; pq.push(make_pair(0,s));
	while(!pq.empty()) {
		pair<int,int> u = pq.top(); pq.pop();
		if(u.first > dist[s][u.second]) continue;
		for(int i = 0; i < adjList[u.second].size(); i++) {
			pair<int,int> v = adjList[u.second][i];
			if(v.second+dist[s][u.second] < dist[s][v.first]) {
				dist[s][v.first] = v.second + dist[s][u.second];
				pq.push(pair<int,int>(dist[s][v.first],v.first));
			}
		}
	}
}

//returns the sum of the shortest paths from all occupied vertices to s
int longest(int s) {
	int sum = 0;
	for(int i = 0; i < P&&sum<mini; i++) {
		sum+=dist[i][s]*occupied[i];
	}
	return sum;
}

int main() {
	freopen("butter.in","r",stdin);
	freopen("butter.out","w",stdout);

	//take input
	scanf("%d %d %d",&N,&P,&C);
	fill(occupied,occupied+810,false);
	for(int i = 0; i < N; i++) {
		int t; scanf("%d",&t);
		occupied[t-1]++;
	}

	//fill adjList
	int a, b, d;
	for(int i = 0; i < C; i++) {
		scanf("%d %d %d",&a,&b,&d);
		adjList[a-1].push_back(pair<int,int>(b-1,d));
		adjList[b-1].push_back(pair<int,int>(a-1,d));
	}

	//call dijkstras on only nodes occupied with cows
	for(int i = 0; i < P; i++) {
		if(occupied[i]) dijkstras(i);
	}

	//find minimum maximum path length to any vertex
	mini = 1000000;
	mini = longest(0);
	for(int i = 1; i < P; i++) {
		mini = min(mini,longest(i));
	}

	printf("%d\n",mini);

	return 0;
}
