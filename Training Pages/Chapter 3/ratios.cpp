/*
ID: lamorea1
LANG: C++11
PROG: ratios
*/
#include <cstdio>
#include <queue>
#include <algorithm>
#include <unordered_set>
using namespace std;

pair<int,pair<int,int>> goal;
pair<int,pair<int,int>> feeds[3];
bool seen[110][110][110];

int check(pair<int,pair<int,int>> a) { //returns whether these feed choices make equal integer multiples of the goal
	pair<int,pair<int,int>> total(0,pair<int,int>(0,0));
	total.first += a.first*feeds[0].first + a.second.first*feeds[1].first + a.second.second*feeds[2].first;
	total.second.first += a.first*feeds[0].second.first + a.second.first*feeds[1].second.first + a.second.second*feeds[2].second.first;
	total.second.second += a.first*feeds[0].second.second + a.second.first*feeds[1].second.second + a.second.second*feeds[2].second.second;
	
	if(goal.first==0&&goal.second.first==0&&goal.second.second==0) {
		if(total.first==0&&total.second.first==0&&total.second.second==0) {
			return 0;
		}
	}
	if(goal.first==0&&total.first>0) return -1;
	if(goal.second.first==0&&total.second.first>0) return -1;
	if(goal.second.second==0&&total.second.second>0) return -1;
	vector<int> temp;
	if(goal.first>0) {
		if(total.first%goal.first==0)
			temp.push_back(total.first/goal.first);
		else return -1;
	}
	if(goal.second.first>0) {
		if(total.second.first%goal.second.first==0)
			temp.push_back(total.second.first/goal.second.first);
		else return -1;
	}
	if(goal.second.second>0) {
		if(total.second.second%goal.second.second==0)
			temp.push_back(total.second.second/goal.second.second);
		else return -1;
	}
	for(int i = 1; i < temp.size(); i++) {
		if(temp[i]!=temp[i-1]) return -1;
	}

	return temp[0];
}

void bfs() { //searches for the smallest fead ratio that satisfies the above method
	queue<pair<int,pair<int,int>>> q;
	q.push(pair<int,pair<int,int>>(1,pair<int,int>(0,0)));
	q.push(pair<int,pair<int,int>>(0,pair<int,int>(1,0)));
	q.push(pair<int,pair<int,int>>(0,pair<int,int>(0,1)));
	while(!q.empty()) {
		pair<int,pair<int,int>> t = q.front(); q.pop();
		if(seen[t.first][t.second.first][t.second.second]) continue; //removes duplicates in our queue
		if(check(t)!=-1) {
			printf("%d %d %d %d\n",t.first,t.second.first,t.second.second,check(t));
			return;
		}
		seen[t.first][t.second.first][t.second.second] = true;
		if(t.first<100)
		q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first,t.second.second)));
		if(t.second.first<100)
		q.push(pair<int,pair<int,int>>(t.first,pair<int,int>(t.second.first+1,t.second.second)));
		if(t.second.second<100)
		q.push(pair<int,pair<int,int>>(t.first,pair<int,int>(t.second.first,t.second.second+1)));
	}
	printf("NONE\n");
}

int main() {
	freopen("ratios.in","r",stdin);
	freopen("ratios.out","w",stdout);

	//take input
	scanf("%d %d %d",&goal.first,&goal.second.first,&goal.second.second);
	scanf("%d %d %d",&feeds[0].first,&feeds[0].second.first,&feeds[0].second.second);
	scanf("%d %d %d",&feeds[1].first,&feeds[1].second.first,&feeds[1].second.second);
	scanf("%d %d %d",&feeds[2].first,&feeds[2].second.first,&feeds[2].second.second);

	fill(&seen[0][0][0],&seen[0][0][0]+110*110*110, false);

	bfs();

	return 0;
}
