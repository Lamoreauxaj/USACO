/*
ID: lamorea1
LANG: C++
PROG: gift1
*/
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

struct comp {
	bool operator()(char* a, char* b) const {
		return strcmp(a,b)<0;
}};

char people[20][20];
map<char*,int,comp> money;
int NP;


int main() {
	freopen("gift1.in","r",stdin);
	freopen("gift1.out","w",stdout);

	//take in names and set net gain to 0
	scanf("%d",&NP);
	for(int i = 0; i < NP; i++) {
		scanf("%s",people[i]);
		money[people[i]] = 0;
	}

	//process transactions
	char giver[20]; char receiver[20]; int NG, split;
	while(scanf("%s\n%d %d",giver,&split,&NG)!=EOF) {
		if(NG==0) continue;
		split/=NG;
		money[giver] -= split*NG;

		for(int j = 0; j < NG&&scanf("%s",receiver); j++)
			money[receiver] += split;

	}

	//output answers
	for(int i = 0; i < NP; i++) printf("%s %d\n",people[i],money[people[i]]);

	return 0;
}
