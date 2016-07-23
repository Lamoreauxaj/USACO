/*
ID: lamorea1
LANG: C++
PROG: wormhole
*/
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;

int N;
int partner[15];
int right[15];
pair<int,int> wormholes[15];
struct comp {
	bool operator()(pair<int,int> a, pair<int,int> b) { if(a.second!=b.second) return a.second < b.second; else return a.first < b.first; }
};

//returns true if no infinite cycles were found
bool isinfinite() {
	int donttry = 0;
	for(int start = 0; start < N; start++) { // while not all visited
		if((donttry&(1<<start))==(1<<start)) continue;
		int pos = start;
		int bitmask = 0; //keeps track of which ones were visited

		//perform movement from this pos until right[pos] == -1 or bitmask contains pos
		donttry|=(1<<pos);
		while(true) {
			if((bitmask&(1<<pos))==(1<<pos)) return true; // if already visited
			bitmask|=(1<<pos);
			pos = right[partner[pos]];
			donttry|=(1<<pos);
			if(pos==-1) break; // not an infinite loop but we're not done yet must keep checking other pos
		}

	}
	return false;
}

//recurse through all solution space
//recursing is faster than next_perm and checking if its valid which is N!*N^2 runtime while this is N^3
int solve() {
	int unpaired;
	//find first unpaired
	for(unpaired = 0; unpaired < N; unpaired++) {
		if(partner[unpaired]==-1) break;
	}
	//if everything is paired
	if(unpaired==N) {
		if(isinfinite()) return 1;
		else return 0;
	}

	//try new pairings and call recusion again
	int count = 0;
	for(int j = unpaired+1; j < N; j++) {
		if(partner[j]!=-1) continue;
		partner[j] = unpaired;
		partner[unpaired] = j;
		count += solve();
		partner[j] = partner[unpaired] = -1; //backtrack and reset to try other pairs
	}
	return count;
}

int main() {
	freopen("wormhole.in","r",stdin);
	freopen("wormhole.out","w",stdout);

	//take input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) scanf("%d %d",&wormholes[i].first,&wormholes[i].second);

	//initialize right array by sorting them
	sort(wormholes,wormholes+N,comp());
	for(int i = 0; i < N; i++) {
		for(int i = 0; i < N; i++)//init right array with -1
			right[i] = -1;
		for(int i = 0; i < N-1; i++) {
			if(wormholes[i].second==wormholes[i+1].second) { // if on same height set the left one's right to the right one
				right[i] = i+1;
			}
		}
	}
	//init partner array to no partners
	for(int i = 0; i < N; i++) partner[i] = -1;

	//call the recursive method
	int count = solve();

	printf("%d\n",count);

	return 0;
}
