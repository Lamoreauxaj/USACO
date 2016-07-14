/*
ID: lamorea1
LANG: C++11
PROG: fence6
*/
#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;

struct fence {
	int l;
	int n1;
	int n2;
	int n1f[10];
	int n2f[10];
};
fence fence(int l, int n1, int n2, int n1f[10], int n2f[10]) {
	struct fence ret;
	ret.l = l; ret.n1 = n1; ret.n2 = n2; for(int i = 0; i < n1; i++) ret.n1f[i] = n1f[i]; for(int i = 0; i < n2; i++) ret.n2f[i] = n2f[i];
	return ret;
}

int N;
struct fence fences[105];
//returns 0 if lastfence is located in currfence's n1f array or 1 if it's in n2f array
int whichside(int lastfence, int currfence) {
	for(int i = 0; i < fences[currfence].n1; i++) if(fences[currfence].n1f[i]==lastfence) return 1;
	for(int i = 0; i < fences[currfence].n2; i++) if(fences[currfence].n2f[i]==lastfence) return 0;
	return 0;
}

int startfence;
int mini;
void recurse(int lastfence, int currfence, int dist, bitset<105> visited) {
	visited[currfence] = true;
	if(currfence==startfence&&dist>0) { //if returned back to starting fence
		mini = min(mini,dist);
	}
	if(whichside(lastfence,currfence)==0) { //go in the n1 direction away from where we came
		for(int i = 0; i < fences[currfence].n1; i++) {
			if(visited[fences[currfence].n1f[i]]&&fences[currfence].n1f[i]!=startfence) continue; //if already been there and it's not the start fence
			recurse(currfence,fences[currfence].n1f[i],dist+fences[currfence].l,visited);
		}
	}else { //go in the n2 direction away from where we came
		for(int i = 0; i < fences[currfence].n2; i++) {
			if(visited[fences[currfence].n2f[i]]&&fences[currfence].n2f[i]!=startfence) continue; //if already been there and it's not the start fence
			recurse(currfence,fences[currfence].n2f[i],dist+fences[currfence].l,visited);
		}
	}
}

int main() {
	freopen("fence6.in","r",stdin);
	freopen("fence6.out","w",stdout);

	//input
	int s, l, n1, n2; int n1f[10]; int n2f[10];
	scanf("%d",&N);
	for(int i = 0; i < N; i++)  {
		scanf("%d %d %d %d",&s, &l, &n1, &n2);
		for(int j = 0; j < n1; j++) scanf("%d",&n1f[j]);
		for(int j = 0; j < n2; j++) scanf("%d",&n2f[j]);
		fences[s] = fence(l,n1,n2,n1f,n2f);
	}

	//find mini
	mini = 1000000000;
	for(int i = 0; i < N; i++) {
		startfence = i;
		recurse(-1,i,0,bitset<105>());
	}

	//output
	printf("%d\n",mini);

	return 0;
}
