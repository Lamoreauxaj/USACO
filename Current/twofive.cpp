/*
ID: lamorea1
LANG: C++11
PROG: twofive
*/
#include <cstdio>
#include <unordered_map>
#include <string>
using namespace std;

int N;

unordered_map<string,int> memo;
int possible(string s) {
	if(memo.count(s)) return memo[s];
	int sum = 0;
	for(int r = 0; r < 5; r++) {
		for(int c = 0; c < 5; c++) {
			if((c==0 || s[r*5+c-1] != '.') && s[r*5+c] == '.' && (r==0 || s[r*5+c-5] != '.')) {
				s[r*5+c] = '*';
				sum += possible(s);
				s[r*5+c] = '.';
			}
		}
	}
	if(sum==0) return memo[s] = 1;
	else return memo[s] = sum;
}

int findindex(string s) {
	int sum = 0;
	string curr = ".........................";
	for(int l = 'A'; l < 'Z'; l++) {
		bool end = false;
		for(int r = 0; r < 5&&!end; r++) {
			for(int c = 0; c < 5&&!end; c++) {
				if(l == s[r*5+c]) curr[r*5+c] = '*', end = true;
				else if((c==0 || curr[r*5+c-1] != '.') && curr[r*5+c] == '.' && (r==0 || curr[r*5+c-5] != '.')) {
					curr[r*5+c] = '*';
					sum += possible(curr);
					curr[r*5+c] = '.';
				}
			}
		}
	}
	return sum + 1;
}

string findword(int n) {
	string ret = ".........................";
	string curr =".........................";
	for(int l = 'A'; l < 'Z'; l++) {
		bool end = false;
		int sum = 0;
		for(int r = 0; r < 5&&!end; r++) {
			for(int c = 0; c < 5&&!end; c++) {
				if((c==0 || curr[r*5+c-1] != '.') && curr[r*5+c] == '.' && (r==0 || curr[r*5+c-5] != '.')) {
					curr[r*5+c] = '*';
					sum += possible(curr);
					if(sum >= n) {//this this path includes the index we are looking for
						end = true;
						ret[r*5+c] = l;
						n = n - (sum - possible(curr));//reset the new index to look for in this subtree
					}
					else curr[r*5+c] = '.';
				}
			}
		}
	}
	return ret;
}

int main() {
	freopen("twofive.in","r",stdin);
	freopen("twofive.out","w",stdout);

	//input
	char act;
	scanf("%c",&act);
	if(act=='N') {
		scanf("%d",&N);
		printf("%s\n",findword(N).c_str());
	}else if(act=='W') {
		char look[30];
		scanf("%s",look);
		printf("%d\n",findindex(string(look)));
	}

	return 0;
}