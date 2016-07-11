/*
ID: lamorea1
LANG: C++11
PROG: msquare
*/
#include <cstdio>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <queue>
using namespace std;

int goal;
unordered_set<int> seen;

int operateA(int t) {
	int ret = 0;
	while(t>0) {
		ret = ret*10 + t%10;
		t /= 10;
	}
	return ret;
}

int digitat(int t, int digit) {
	int num = 1;
	for(int i = 0; i < digit; i++) {
		num*=10;
	}
	return t % (num*10) / num;
}

int operateB(int t) {
	int ret = 0;
	ret = ret * 10 + digitat(t,4); //3
	ret = ret * 10 + digitat(t,7); //0
	ret = ret * 10 + digitat(t,6); //1
	ret = ret * 10 + digitat(t,5); //2
	ret = ret * 10 + digitat(t,2); //5
	ret = ret * 10 + digitat(t,1); //6
	ret = ret * 10 + digitat(t,0); //7
	ret = ret * 10 + digitat(t,3); //4
	return ret;
}

int operateC(int t) {
	int ret = 0;
	ret = ret * 10 + digitat(t,7); //0
	ret = ret * 10 + digitat(t,1); //6
	ret = ret * 10 + digitat(t,6); //1
	ret = ret * 10 + digitat(t,4); //3
	ret = ret * 10 + digitat(t,3); //4
	ret = ret * 10 + digitat(t,5); //2
	ret = ret * 10 + digitat(t,2); //5
	ret = ret * 10 + digitat(t,0); //7
	return ret;
}

void print(string t) {
	printf("%s\n",t.substr(0,60).c_str());
	for(int i = 60; i < t.size(); i+=60) {
		printf("%s\n",t.substr(i,60).c_str());
	}
}

void bfs() {
	queue<pair<string,int>> qu;
	qu.push(make_pair(string(""),12345678));
	while(!qu.empty()) {
		pair<string,int> t = qu.front(); qu.pop();
		if(seen.count(t.second)) continue;
		if(t.second==goal) {
			printf("%d\n",int(t.first.size()));
			print(t.first);
			return;
		}
		seen.insert(t.second);
		if(t.first[t.first.size()-1]!='A') {
			qu.push(make_pair(t.first+"A",operateA(t.second)));
		}
		qu.push(make_pair(t.first+"B",operateB(t.second)));
		qu.push(make_pair(t.first+"C",operateC(t.second)));
	}
}

int main() {
	freopen("msquare.in","r",stdin);
	freopen("msquare.out","w",stdout);

	//take input
	int t;
	for(int i = 0; i < 8; i++) {
		scanf("%d",&t); 
		goal = goal*10 + t;
	}

	bfs();

	return 0;
}
