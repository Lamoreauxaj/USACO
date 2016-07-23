/*
ID: lamorea1
LANG: C++11
PROG: tour
*/
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int N, V;
unordered_map<string, int> loc;
vector<int> adjList[100];

int memo[100][100];

int dp(int one, int two) { //returns the maximum sum of both paths when two travelers at pos one and pos two travel eastward never overlapping on cities
	if(one==two&&two==N-1) return 0; //if both are at eastern most city
	if(memo[one][two]!=-1) return memo[one][two]; //if already calculated
	int maxi = -1000000000;
	//take western traveler and attempt to travel to all eastern cities not including the one the other traveler is on unless it is the last city
	if(one <= two) {
		for(int i = 0; i < adjList[one].size(); i++) {
			int u = adjList[one][i];
			if(u > one) if(u==N-1||u!=two) maxi = max(maxi,dp(u,two)+1);
		}
	}if(two <= one) {
		for(int i = 0; i < adjList[two].size(); i++) {
			int u = adjList[two][i];
			if(u > two) if(u==N-1||u!=one) maxi = max(maxi,dp(one,u)+1);
		}
	}
	return memo[one][two] = maxi;
}

int main() {
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);


	//input
	scanf("%d %d",&N,&V); char temp[1000]; string a, b;
	for(int i = 0; i < N; i++) {
		scanf("%s",temp);
		a = temp;
		loc[a] = i;
	}
	for(int i = 0; i < V; i++) {
		scanf("%s",temp); a = temp; scanf("%s",temp); b = temp;
		adjList[loc[a]].push_back(loc[b]);
		adjList[loc[b]].push_back(loc[a]);
	}
	fill(memo[0],memo[N-1]+N,-1);

	//output
	if(dp(0,0)<-1000000) printf("1\n");
	else printf("%d\n",dp(0,0));

	return 0;
}
