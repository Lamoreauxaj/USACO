/*
ID: lamorea1
LANG: C++11
PROG: maze1
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;
ifstream in("maze1.in");
ofstream out("maze1.out");

string map[210];
int rows, cols;
int dist[210][100]; //stores dist of r,c from exits

bool inbounds(int r, int c) {
	return c>=0&&r>=0&&r<rows&&c<cols;
}

//locates distance of each cell from startr, startc and compares it to past distances to find distance to closest exit
bool visited[210][210];
void bfs(int startr, int startc) {
	queue<pair<int,pair<int,int> > > qu;
	qu.push(pair<int,pair<int,int> >(0,pair<int,int>(startr,startc)));
	for(int r = 0; r < rows; r++) for(int c = 0; c < cols; c++) visited[r][c] = false;
	while(!qu.empty()) {
		pair<int,pair<int,int> > t = qu.front(); qu.pop();
		if(!inbounds(t.second.first,t.second.second)) continue;
		if(map[t.second.first][t.second.second]!=' ') continue;
		if(visited[t.second.first][t.second.second]) continue;
		visited[t.second.first][t.second.second] = true;
		dist[t.second.first][t.second.second] = min(t.first,dist[t.second.first][t.second.second]);
		qu.push(pair<int,pair<int,int> >(t.first+1,pair<int,int>(t.second.first-1,t.second.second)));
		qu.push(pair<int,pair<int,int> >(t.first+1,pair<int,int>(t.second.first+1,t.second.second)));
		qu.push(pair<int,pair<int,int> >(t.first+1,pair<int,int>(t.second.first,t.second.second-1)));
		qu.push(pair<int,pair<int,int> >(t.first+1,pair<int,int>(t.second.first,t.second.second+1)));
	}
}

int main() {

	//take input
	in >> cols >> rows;
	cols = cols*2+1;
	rows = rows*2+1;

	getline(in,map[0]); //whitespace error
	for(int r = 0; r < rows; r++) {
		getline(in,map[r]);
		for(int c = 0; c < cols; c++) dist[r][c] = 20000;
	}


	//locate blank sides and call bfs from there
	for(int r = 0; r < rows; r++) {
		if(map[r][0]==' ') {
			bfs(r,0);
		}
		if(map[r][cols-1]==' ') {
			bfs(r,cols-1);
		}
	}
	for(int c = 0; c < cols; c++) {
		if(map[0][c]==' ') {
			bfs(0,c);
		}
		if(map[rows-1][c]==' ') {
			bfs(rows-1,c);
		}
	}

	//find furthest cell from either exit
	int maxi = 0;
	for(int r = 0; r < rows; r++)
		for(int c = 0; c < cols; c++) {
			if(map[r][c]!=' ') continue;
			maxi = max(maxi,dist[r][c]);
		}

	out << (maxi+1)/2 << '\n';

	return 0;
}
