/*
ID: lamorea1
LANG: C++
PROG: milk2
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


bool comp(pair<int,int> a, pair<int,int> b) { return a.first < b.first; }

int N;
vector<pair<int,int> > times;

int main() {
	freopen("milk2.in","r",stdin);
	freopen("milk2.out","w",stdout);

	//take input and fill in what times they were milked
	scanf("%d",&N);
	int a, b;
	for(int i = 0; i < N&&scanf("%d %d",&a,&b); i++) {
		times.push_back(pair<int,int>(a,b));
	}

	sort(times.begin(),times.end(),comp);

	//try to merge ones that overlap
	for(int i = 1; i < N; i++) {
		if(times[i].first<=times[i-1].second) {
			times[i-1] = pair<int,int>(times[i-1].first,max(times[i].second,times[i-1].second));
			times.erase(times.begin()+i);
			i--; N--;
		}
	}

	//find the max nonmilk and milk times
	int nonmilk = 0;
	int milk = 0;
	for(int i = 0; i < N; i++)
		milk = max(milk,times[i].second-times[i].first);
	for(int i = 1; i < N; i++)
		nonmilk = max(nonmilk,times[i].first-times[i-1].second);

	printf("%d %d\n",milk,nonmilk);

	return 0;
}
