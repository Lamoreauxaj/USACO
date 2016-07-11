/*
ID: lamorea1
LANG: C++
PROG: ariprog
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int N, M, mm2;
bool bs[125010];
vector<int> bslist;

//creates a lookup table (Array) and a sorted list of all the bisquares
void genbisquares() { int t;
	for(int p = 0; p <= M; p++) {
		for(int q = p; q <= M; q++) {
			t = p*p+q*q;
			bslist.push_back(t);
			bs[t] = true;
		}
	}

	//order the list and remove duplicates
	sort(bslist.begin(),bslist.end());
	for(int i = 1; i < bslist.size(); i++) {
		if(bslist[i]==bslist[i-1]) {
			bslist.erase(bslist.begin()+i);
			i--;
		}
	}
}

//returns if a, a+b, a+2b, a+3b, a+(N-1)b is a valid arithmetic progression
bool checkseq(int a, int b) {
	if(b>5000) return false;
	if(a+(N-1)*b>mm2) return false;
	int sum = a+b+b; // we already know a and a+b work because they were found in the loop that called this method
	for(int i = 2; i < N; sum+=b, i++) {
		if(!bs[sum]) return false;
	}return true;
}

//used to sort the results
bool comp(pair<int,int> a, pair<int,int> b) {
	return (a.second==b.second) ? a.first < b.first : a.second < b.second;
}

int main() {
	freopen("ariprog.in","r",stdin);
	freopen("ariprog.out","w",stdout);

	scanf("%d\n%d",&N,&M);
	mm2 = M*M*2;
	genbisquares();

	// try all possible pairs of i = a, j = a+b
	int num_res = 0;
	pair<int,int> res[1000000];
	bool none = true;
	for(int i = 0; i < bslist.size(); i++) {
		for(int j = i+1; j < bslist.size(); j++) {
			if(checkseq(bslist[i],bslist[j]-bslist[i])) {
				res[num_res++] = pair<int,int>(bslist[i],bslist[j]-bslist[i]);
				none = false;
			}
		}
	}

	// print output
	sort(res,res+num_res,comp);

	for(int i = 0; i < num_res; i++)
		printf("%d %d\n",res[i].first,res[i].second);
	if(none) printf("NONE\n");

	return 0;
}
