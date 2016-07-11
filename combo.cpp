/*
ID: lamorea1
LANG: C++
PROG: combo
*/
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;

int N;
pair<int, pair<int,int> > john; pair<int, pair<int,int> > master;

//returns the shortest number of moves to get from a to b on a dial
int dist(int a, int b) {
	return min(abs(a-b),N-abs(a-b));
}

//returns whether a combination is at most within 2 turns to one of the correct combos
bool isvalid(pair<int, pair<int,int> > combo) {
	return (max(dist(combo.first,john.first),max(dist(combo.second.first,john.second.first),dist(combo.second.second,john.second.second)))) <= 2 || 
	(max(dist(combo.first,master.first),max(dist(combo.second.first,master.second.first),dist(combo.second.second,master.second.second)))) <= 2;
}

int main() {
	freopen("combo.in","r",stdin);
	freopen("combo.out","w",stdout);

	//take input
	scanf("%d",&N);
	scanf("%d %d %d",&john.first,&john.second.first,&john.second.second);
	scanf("%d %d %d",&master.first,&master.second.first,&master.second.second);

	//try all possible combinations and keep count
	int count = 0;
	for(int a = 1; a <= N; a++)
		for(int b = 1; b <= N; b++)
			for(int c = 1; c <= N; c++)
				if(isvalid(pair<int,pair<int,int> >(a,pair<int,int>(b,c)))) {
					count++;
				}

	printf("%d\n",count);

	return 0;
}
