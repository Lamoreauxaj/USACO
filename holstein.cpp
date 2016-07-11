/*
ID: lamorea1
LANG: C++
PROG: holstein
*/
#include <cstdio>
using namespace std;


int main() {
	freopen("holstein.in","r",stdin);
	freopen("holstein.out","w",stdout);

	//take input
	int V, G; int v[30]; int g[30][30];
	scanf("%d",&V);
	for(int i = 0; i < V; i++) scanf("%d",&v[i]);
	scanf("%d",&G);
	for(int i = 0; i < G; i++)
		for(int j = 0; j < V; j++) scanf("%d",&g[i][j]);

	//generate all subsets of the feeds
	int best = (1<<G);
	int bestcount = 25;
	for(int subset = 1; subset < (1<<G); subset++) { //will do lower numbers first
		int temp[30]; for(int i = 0; i < V; i++) temp[i] = v[i];
		int count = 0;
		for(int i = 0; i < G; i++) {
			if(subset&(1<<i)) {
				count++;
				for(int j = 0; j < V; j++) {
					temp[j]-=g[i][j]; //subtract the vitamins of each feed from the requirements in temp
				}
			}
		}
		//check if this is valid (fufills nutrient requirements)
		bool valid = true;
		for(int i = 0; i < V; i++) if(temp[i]>0) valid = false;
		if(valid)
			if(count < bestcount) {
				best = subset; bestcount = count; }
	}

	//print output
	printf("%d",bestcount);
	for(int i = 0; i < G; i++)
		if(best&(1<<i)) printf(" %d",i+1);
	printf("\n");


	return 0;
}
