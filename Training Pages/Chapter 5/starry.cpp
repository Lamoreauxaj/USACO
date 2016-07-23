/*
ID: lamorea1
LANG: C++11
PROG: starry
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct comp {
	bool operator() (vector<vector<char>> a, vector<vector<char>> b) const {
		if(a.size()!=b.size()||a[0].size()!=b[0].size()) return false;
		for(int r = 0; r < a.size(); r++) {
			for(int c = 0; c < a[r].size(); c++) 
				if(a[r][c]!=b[r][c]) return false;
		}return true;
	}
};
struct hf {
	int operator() (vector<vector<char>> a) const {
		int ret = 0;
		for(int i = 0; i < min(12,int(a.size())); i++) ret = ret*2+a[i][0];
		return ret;
	}
};

//rotate and reflect are used to find similar constellations that we should watch out for
vector<vector<char>> rotate(vector<vector<char>> a) { //rotate a counter clockwise
	vector<vector<char>> ret(a[0].size(),vector<char>(a.size(),'0'));
	for(int r = 0; r < a[0].size(); r++) {
		for(int c = 0; c < a.size(); c++) {
			ret[r][c] = a[a.size()-c-1][r];
		}
	}
	return ret;
}

vector<vector<char>> reflect(vector<vector<char>> a) { //reflect a across a vertical line in the middle of it
	vector<vector<char>> ret(a.size(),vector<char>(a[0].size(),'0'));
	for(int r = 0; r < a.size(); r++) {
		int s = 0;
		int e = a[r].size()-1;
		while(s<=e) ret[r][s] = a[r][e], ret[r][e] = a[r][s], s++, e--;
	}
	return ret;
}

int rows, cols;
char sky[100][100];
int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};
unordered_map<vector<vector<char>>,char,hf,comp> uniq;


bool inbounds(int r, int c) {return r>=0&&c>=0&&r<rows&&c<cols;}
void update(int r, int c, char let) {//floodfills r,c with the char let
	if(!inbounds(r,c)||sky[r][c]!='1') return;
	sky[r][c] = let;
	for(int i = 0; i < 8; i++) update(r+dr[i],c+dc[i],let);
}

vector<vector<char>> boundingbox(int r, int c) {//returns a matrix that contains a box that surrounds the constellation that contains r,c
	//find corners of the box (size of the image)
	int minr = 1000, minc = 1000, maxr = -1, maxc = -1;
	queue<pair<int,int>> q; q.push(pair<int,int>(r,c));
	vector<vector<bool>> visited(rows,vector<bool>(cols,false));
	while(!q.empty()) {
		pair<int,int> u = q.front(); q.pop();
		if(!inbounds(u.first,u.second)||sky[u.first][u.second]!='1'||visited[u.first][u.second]) continue;
		visited[u.first][u.second] = true;
		minr = min(u.first,minr);
		minc = min(u.second,minc);
		maxr = max(u.first,maxr);
		maxc = max(u.second,maxc);
		for(int i = 0; i < 8; i++) q.push(pair<int,int>(u.first+dr[i],u.second+dc[i]));
	}

	//create and fill the image of the constellation
	vector<vector<char>> image(maxr-minr+1,vector<char>(maxc-minc+1,'0'));
	q.push(pair<int,int>(r,c));
	while(!q.empty()) {
		pair<int,int> u = q.front(); q.pop();
		if(!inbounds(u.first,u.second)||sky[u.first][u.second]!='1'||image[u.first-minr][u.second-minc]!='0') continue;
		image[u.first-minr][u.second-minc] = '1';
		for(int i = 0; i < 8; i++) q.push(pair<int,int>(u.first+dr[i],u.second+dc[i]));
	}

	return image;
}

int main() {
	freopen("starry.in","r",stdin);
	freopen("starry.out","w",stdout);

	//input
	scanf("%d %d",&cols,&rows); char line[105];
	for(int i = 0; i < rows&&scanf("%s",line); i++) for(int j = 0; j < cols; j++) sky[i][j] = line[j];

	//label all the constellations
	int let = 'a';
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			if(sky[r][c]=='1') {
				vector<vector<char>> b = boundingbox(r,c);
				if(uniq.count(b)) update(r,c,uniq[b]);
				else {
					uniq[b] = let;
					uniq[reflect(b)] = let;
					b = rotate(b);
					uniq[b] = let;
					uniq[reflect(b)] = let;
					b = rotate(b);
					uniq[b] = let;
					uniq[reflect(b)] = let;
					b = rotate(b);
					uniq[b] = let;
					uniq[reflect(b)] = let;
					update(r,c,let++);
				}
			}
		}
	}

	//output
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) printf("%c",sky[i][j]);
		printf("\n");
	}

	return 0;
}
