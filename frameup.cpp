/*
ID: lamorea1
LANG: C++11
PROG: frameup
*/
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

char map[30][30];
int rows, cols;
vector<pair<pair<int,int>,pair<int,int>>> positions;

int check(int rr, int cc, int rsz, int csz, char map[30][30]) {//returns true(ch) or false(-1) if map contains a frame that spans rsz and csz characters (contains means that that area contains only a single letter or # signs)
	char ch = '!';
	for(int r = rr; r < rr+rsz; r++) {
		if(map[r][cc]=='.') return -1;
		else if(map[r][cc]=='#') continue;
		else {
			if(ch=='!') ch = map[r][cc];
			else {
				if(map[r][cc]==ch) continue;
				else return -1;
			}
		}
	}
	for(int r = rr; r < rr+rsz; r++) {
		if(map[r][cc+csz-1]=='.') return -1;
		else if(map[r][cc+csz-1]=='#') continue;
		else {
			if(ch=='!') ch = map[r][cc+csz-1];
			else {
				if(map[r][cc+csz-1]==ch) continue;
				else return -1;
			}
		}
	}
	for(int c = cc; c < cc+csz; c++) {
		if(map[rr][c]=='.') return -1;
		else if(map[rr][c]=='#') continue;
		else {
			if(ch=='!') ch = map[rr][c];
			else {
				if(map[rr][c]==ch) continue;
				else return -1;
			}
		}
	}
	for(int c = cc; c < cc+csz; c++) {
		if(map[rr+rsz-1][c]=='.') return -1;
		else if(map[rr+rsz-1][c]=='#') continue;
		else {
			if(ch=='!') ch = map[rr+rsz-1][c];
			else {
				if(map[rr+rsz-1][c]==ch) continue;
				else return -1;
			}
		}
	}
	if(ch=='!') return -1;
	else return ch;
}

vector<string> ans;

int sol[50];
int sol_size;
void dfs(char map[30][30]) {
	bool found = false;
	for(int i = 0; i < positions.size(); i++) { //try all possible ones to remove
		int rr = positions[i].first.first; int cc = positions[i].first.second; int rsz = positions[i].second.first; int csz = positions[i].second.second;
		char t = check(rr,cc,rsz,csz,map);
		if(t!=-1) {
			//clear this frame
			char pass[30][30];
			for(int r = 0; r < rows; r++) for(int c = 0; c < cols; c++) pass[r][c] = map[r][c];
			for(int r = rr; r < rr + rsz; r++) {
				pass[r][cc] = '#';
				pass[r][cc+csz-1] = '#';
			}
			for(int c = cc; c < cc + csz; c++) {
				pass[rr][c] = '#';
				pass[rr+rsz-1][c] = '#';
			}
			sol[sol_size++] = t;
			dfs(pass); //recurse
			sol_size--;
			found = true;
		}
	}

	if(!found) { //if this is a leaf in the recursion (means all were removed)
		string temp;
		for(int i = 0; i < sol_size; i++) temp+=char(sol[i]);
		reverse(temp.begin(),temp.end());
		ans.push_back(temp);
	}
}

void findpositions() {// fills positions vector with locations of all the frames
	for(char i = 'A'; i <= 'Z'; i++) {
		int minr = 1000000000;
		int maxr = -1;
		int minc = 1000000000;
		int maxc = -1;
		for(int r = 0; r < rows; r++) {
			for(int c = 0; c < cols; c++) {
				if(map[r][c]==i) {
					minr = min(minr,r);
					maxr = max(maxr,r);
					minc = min(minc,c);
					maxc = max(maxc,c);
				}
			}
		}
		if(maxr!=-1) {
			positions.push_back(pair<pair<int,int>,pair<int,int>>(pair<int,int>(minr,minc),pair<int,int>(maxr-minr+1,maxc-minc+1)));
		}
	}
}

int main() {
	freopen("frameup.in","r",stdin);
	freopen("frameup.out","w",stdout);

	//input
	scanf("%d %d",&rows,&cols);
	for(int r = 0; r < rows; r++) {
		char line[30]; scanf("%s",line);
		for(int c = 0; c < cols; c++)
			map[r][c] = line[c];
	}

	//call dfs
	findpositions();
	sol_size = 0;
	dfs(map);

	//output
	sort(ans.begin(),ans.end());
	for(int i = 0; i < ans.size(); i++) printf("%s\n",ans[i].c_str());

	return 0;
}
