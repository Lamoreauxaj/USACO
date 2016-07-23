/*
ID: lamorea1
LANG: C++11
PROG: lgame
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

struct comp {
	bool operator() (const char* lhs, const char* rhs) const {
		return strcmp(lhs,rhs) < 0;
	}
};

int cmp(char* word, pair<int,int>& a, pair<int,int>& b) {
	for(int i = 0; i < min(a.second,b.second); i++) {
		if(word[a.first+i] < word[b.first+i]) return -1;
		else if(word[a.first+i] > word[b.first+i]) return 1;
	}
	if(a.second>b.second) return -1;
	else if(b.second>a.second) return 1;
	else return 0;
}

bool eq(vector<char*> a, vector<char*> b) {
	if(a.size()!=b.size()) return false;
	for(int i = 0; i < a.size(); i++) if(strcmp(a[i],b[i])!=0) return false;
	return true;
}

bool les(vector<char*> a, vector<char*> b) {
	for(int i = 0; i < min(a.size(),b.size()); i++) {
		if(strcmp(a[i],b[i]) < 0) return true;
		else if(strcmp(a[i],b[i]) > 0) return false;
	}
	if(a.size() < b.size()) return true;
	if(a.size() > b.size()) return false;
	return false;
}

set<char*,comp> dict;

int main() {
	freopen("lgame.in","r",stdin);
	freopen("lgame.out","w",stdout);

	int val[] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};

	char word[10]; scanf("%s",word);
	int wlen = strlen(word);
	int twlen = 1<<wlen;

	//fill dict
	freopen("lgame.dict","r",stdin);
	while(true) {
		char* temp = new char[10];
		scanf("%s",temp); if(strcmp(temp,".")==0) break;
		dict.insert(temp);
	}

	int maxi = 0;
	vector<vector<char*>> best;

	for(int i = 0; i < twlen; i++) { //try all subsets of the letters
		//create available letters
		char avail[10]; int alen = 0;
		for(int j = 0; j < wlen; j++) if(i&(1<<j)) avail[alen++] = word[j];
		avail[alen] = '\0';
		sort(avail,avail+alen);
		int talen = 1<<(alen-1);

		//calc score of these letters
		int score = 0;
		for(int k = 0; k < alen; k++) {
			score += val[avail[k]-'a'];
		}
		if(score < maxi) continue;
		do {//try all orderings of the letter

			//try all splitting points of the letters
			for(int j = 0; j < talen; j++) {
				vector<pair<int,int>> splits;
				int s = 0, len = 0;
				len++;
				for(int k = 1; k < alen; k++) {
					if((1<<(k-1))&j) {
						splits.push_back(pair<int,int>(s,len));
						s = k;
						len = 0;
					}
					len++;
				}splits.push_back(pair<int,int>(s,len));

				char temp[10];
				vector<char*> ans;
				for(int j = 0; j < splits.size(); j++) {
					for(int i = 0; i < splits[j].second; i++) temp[i] = avail[splits[j].first+i];
					temp[splits[j].second] = '\0';
					if(j>0 && cmp(avail,splits[j],splits[j-1]) < 0) break; //make sure they are only in alphabetical order
					if(dict.count(temp)) { //see if the dict contains all the words we need
						ans.push_back(new char[10]);
						strcpy(ans[ans.size()-1],temp);
					}
				}
				if(ans.size()==splits.size()) {
					if(score==maxi) {
						best.push_back(ans);
					}else if(score > maxi) {
						best.clear();
						best.push_back(ans);
						maxi = score;
					}
				}

			}

		}while(next_permutation(avail,avail+alen));
	}

	printf("%d\n",maxi);
	sort(best.begin(),best.end(),les);
	for(int i = 1; i < best.size(); i++) {
		if(eq(best[i],best[i-1])) best.erase(best.begin()+i), i--;
	}
	for(int i = 0; i < best.size(); i++) {
		for(int j = 0; j < best[i].size(); j++) {
			if(j>0) printf(" ");
			printf("%s",best[i][j]);
		}
		printf("\n");
	}

	return 0;
}
