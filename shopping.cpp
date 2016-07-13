/*
ID: lamorea1
LANG: C++11
PROG: shopping
*/
#include <cstdio>
#include <algorithm>
using namespace std;

struct offer {
	int n;
	pair<int,int> items[5];
	int p;
} offers[103];
int code[1010];
int amt[6];
int price[6];
int S, B;
int knap[6][6][6][6][6];
int main() {
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);

	//input
	scanf("%d",&S);
	for(int i = 0; i < S; i++) {
		scanf("%d",&offers[i].n);
		for(int j = 0; j < offers[i].n; j++) {
			scanf("%d %d",&offers[i].items[j].first,&offers[i].items[j].second);
		}scanf("%d",&offers[i].p);
	}
	scanf("%d",&B);
	fill(amt,amt+6,0); fill(price,price+6,0);
	for(int i = 0; i < B; i++) {
		int t; scanf("%d",&t);
		code[t] = i;
		scanf("%d %d",&amt[i],&price[i]);
	}

	//fill initial values (no special offers)
	for(int a = 0; a < 6; a++)
		for(int b = 0; b < 6; b++)
			for(int c = 0; c < 6; c++)
				for(int d = 0; d < 6; d++)
					for(int e = 0; e < 6; e++)
						knap[a][b][c][d][e] = a*price[0]+b*price[1]+c*price[2]+d*price[3]+e*price[4];

	//process	
	for(int a = 0; a < 6; a++)
	for(int b = 0; b < 6; b++)
	for(int c = 0; c < 6; c++)
	for(int d = 0; d < 6; d++)
	for(int e = 0; e < 6; e++)	//try all amounts of each item
	for(int i = 0; i < S; i++) { //try all special offers
		int t[] = {a,b,c,d,e};
		bool good = true;
		for(int j = 0; j < offers[i].n; j++) {
			t[code[offers[i].items[j].first]] -= offers[i].items[j].second;
			if(t[code[offers[i].items[j].first]]<0) good = false;
		}
		if(!good) continue; //can't take this offer (ie don't have the items)
		knap[a][b][c][d][e] = min(knap[a][b][c][d][e],knap[t[0]][t[1]][t[2]][t[3]][t[4]]+offers[i].p);
	}

	//output
	printf("%d\n",knap[amt[0]][amt[1]][amt[2]][amt[3]][amt[4]]);

	return 0;
}
