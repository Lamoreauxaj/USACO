/*
ID: lamorea1
LANG: C++11
PROG: camelot
*/
#include <cstdio>
#include <vector>
#include <cmath>
#include <set>
#include <queue>
#include <cstdlib>
using namespace std;

int rows, cols;
pair<int,int> king;
vector<pair<int,int>> knights;
int mini;

int dist[35][35][35][35];

void filldist() { //fills dist array with dist for each knight to get from its spot to all other spots
	fill(&dist[0][0][0][0],&dist[0][0][0][0]+35*35*35*35,1000000000);
	for(int r = 0; r < rows; r++) 
	for(int c = 0; c < cols; c++) { 
		queue<pair<int,pair<int,int>>> q;
		q.push(pair<int,pair<int,int>>(0,pair<int,int>(r,c)));
		while(!q.empty()) { //basic bfs
			pair<int,pair<int,int>> t = q.front(); q.pop();
			if(t.second.first<0||t.second.second<0||t.second.first>=rows||t.second.second>=cols) continue;
			if(dist[r][c][t.second.first][t.second.second]!=1000000000) continue;
			dist[r][c][t.second.first][t.second.second] = t.first;
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first+1,t.second.second+2)));
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first+1,t.second.second-2)));
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first-1,t.second.second+2)));
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first-1,t.second.second-2)));
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first+2,t.second.second+1)));
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first+2,t.second.second-1)));
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first-2,t.second.second+1)));
			q.push(pair<int,pair<int,int>>(t.first+1,pair<int,int>(t.second.first-2,t.second.second-1)));
		}
	}
}

int sum(int r, int c) { //returns total sum of moves it takes for all pieces to traveling to dst if they travel minimally
	int total = 0;
	for(int i = 0; i < knights.size(); i++) {
		total+=dist[knights[i].first][knights[i].second][r][c];
		if(total>mini) return total;
	}
	int kingdist = max(abs(king.first-r),abs(king.second-c));
	//see if a king traveling with the knight is better than letting the king travel on its own
	for(int i = 0; i < knights.size(); i++) {
		int tmp = 0;
		for(int rr = max(0,king.first-2); rr <= min(rows-1,king.first+2); rr++) //must check a 5x5 box around the king as possibible for 
		for(int cc = max(0,king.second-2); cc <= min(cols-1,king.second+2); cc++) { //king to move to before meeting a knight
			tmp = max(abs(rr-king.first),abs(cc-king.second)) + (dist[knights[i].first][knights[i].second][rr][cc] + dist[rr][cc][r][c] - dist[knights[i].first][knights[i].second][r][c]); 
			// ^^^^ how much more the knight must travel if he travels with the king ^^^^
			if(tmp < kingdist) kingdist = tmp;
		}
	}
	return total + kingdist;
}

int main() {
	freopen("camelot.in","r",stdin);
	freopen("camelot.out","w",stdout);

	//input
	scanf("%d %d",&cols,&rows); //wow... I hate this line of code... took forever to find this error.. fml
	char tc; int t;
	scanf(" %c %d",&tc,&t);
	king = pair<int,int>(tc-'A',t-1);
	while(scanf(" %c %d",&tc,&t)!=EOF) {
		knights.push_back(pair<int,int>(tc-'A',t-1));
	}

	filldist();

	//try all spots and keep min
	mini = 1000000000;
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++)
			mini = min(mini,sum(r,c));
	}
	//output
	printf("%d\n",mini);

	return 0;
}
