/*
ID: lamorea1
LANG: C++11
PROG: charrec
*/
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

int N;
char letters[27][20][20];
char text[1200][20];
pair<int,string> memo[1200];
int corr[1200][27][20];

int countcorruption(int pos, int let) {
	int count = 0;
	for(int i = 0; i < 20; i++) {
		count += corr[i+pos][let][i];
	}
	return count;
}
int countcorruptionmissing(int pos, int ignore, int let) {
	int count = 0;
	for(int i = 0; i < 20; i++) { if(i == ignore) continue;
		count += corr[(i>ignore)?i-1+pos:i+pos][let][i];
	}
	return count;
}
int countcorruptiondupe(int pos, int ignore, int let) {
	int count = 0;
	for(int i = 0; i < 21; i++) { if(i == ignore) continue;
		count += corr[i+pos][let][(i>ignore)?i-1:i];
	}
	return count;
}

pair<int,string> dp(int pos) { //returns string and minimum number of corruptions to reach that string starting at pos i to the end of text
	if(pos==N) return pair<int,string>(0,string());
	if(memo[pos].first!=-1) return memo[pos];
	pair<int,string> best(1000000000,string());
	if(pos <= N-19) {//try all possible characters with missing lines
		pair<int,string> t = dp(pos+19);
		int mini = 1000000000;
		char let;
		for(int i = 0; i < 27; i++) for(int j = 0; j < 20; j++) {
			int temp = countcorruptionmissing(pos,j,i);
			if(temp < mini) mini = temp, let = i+'a'-1;
		}
		t.second += let; t.first += mini;
		if(t.first < best.first) best = t;
	}
	if(pos <= N-20) {//try all possible characters with not dupe or missing lines
		pair<int,string> t = dp(pos+20);
		int mini = 1000000000;
		char let;
		for(int i = 0; i < 27; i++) {
			int temp = countcorruption(pos,i);
			if(temp < mini) mini = temp, let = i+'a'-1;
		}
		t.second += let; t.first += mini;
		if(t.first < best.first) best = t;
	}
	if(pos <= N-21) {//try all possible characters with dupe lines
		pair<int,string> t = dp(pos+21);
		int mini = 1000000000;
		char let;
		for(int i = 0; i < 27; i++) for(int j = 0; j < 21; j++) {
			int temp = countcorruptiondupe(pos,j,i);
			if(temp < mini) mini = temp, let = i+'a'-1;
		}
		t.second += let; t.first += mini;
		if(t.first < best.first) best = t;
	}
	return memo[pos] = best;
}

int main() {
	freopen("font.in","r",stdin);
	freopen("charrec.out","w",stdout);

	//input
	scanf("%d",&N); char line[25];
	for(int i = 0; i < N; i++) {
		scanf("%s",line);
		for(int j = 0; j < 20; j++) {
			letters[i/20][i%20][j] = line[j];
		}
	}
	freopen("charrec.in","r",stdin);
	scanf("%d",&N);
	for(int i = 0; i < N; i++) {
		scanf("%s",line);
		for(int j = 0; j < 20; j++) {
			text[i][j] = line[j];
		}
	}
	fill(memo,memo+N,pair<int,string>(-1,string()));

	//fill corr array
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < 27; j++) {
			for(int k = 0; k < 20; k++) {
				int count = 0;
				for(int m = 0; m < 20; m++) {
					if(text[i][m] != letters[j][k][m]) count++;
				}
				corr[i][j][k] = count;
			}
		}
	}

	//output
	pair<int,string> ans = dp(0);
	for(int i = ans.second.size()-1; i >= 0; i--) {
		if(ans.second[i]=='a'-1) printf(" ");
		else printf("%c",ans.second[i]);
	}printf("\n");

	return 0;
}
