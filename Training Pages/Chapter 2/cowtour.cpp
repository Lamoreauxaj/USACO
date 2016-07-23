/*
ID: lamorea1
LANG: C++11
PROG: cowtour
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int inf = 1000000000;

double dist[155][155];
pair<int,int> vertex[155];

double distance(int i, int j) {
	return sqrt(pow(vertex[i].first-vertex[j].first,2)+pow(vertex[i].second-vertex[j].second,2));
}

int main() {
	freopen("cowtour.in","r",stdin);
	freopen("cowtour.out","w",stdout);

	//take input and fill dist array
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d %d",&vertex[i].first,&vertex[i].second);

	char line[200];
	for(int i = 0; i < n; i++) {
		scanf("%s",line);
		for(int j = 0; j <= i; j++) {
			if(i==j) {
				dist[i][j] = 0;
				continue;
			}
			if(line[j]=='1') {
				dist[i][j] = dist[j][i] = distance(i,j);
			}else dist[i][j] = dist[j][i] = inf;
		}
	}

	//preform floyd warshall's
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++) {
				dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
			}

	//find longest diameter creatable
	double di = inf;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < i; j++) {
			if(dist[i][j]<inf) continue;

			double dii = 0;//past diameter in field with pasture i
			double dij = 0;//past diameter in field with pasture j
			for(int k = 0; k < n; k++) {if(dist[i][k]>=inf) continue;
				for(int m = 0; m < k; m++) {if(dist[i][m]>=inf) continue;
					dii = max(dii,dist[k][m]);
				}
			}
			for(int k = 0; k < n; k++) {if(dist[j][k]>=inf) continue;
				for(int m = 0; m < k; m++) {if(dist[j][m]>=inf) continue;
					dij = max(dij,dist[k][m]);
				}
			}

			double longesti = 0;//longest path from i to other nodes within its component
			double longestj = 0;//longest path from j to other nodes within its component
			for(int k = 0; k < n; k++) {
				if(dist[i][k]>=inf) continue;
				longesti = max(longesti,dist[i][k]);
			}
			for(int k = 0; k < n; k++) {
				if(dist[j][k]>=inf) continue;
				longestj = max(longestj,dist[j][k]);
			}

			//MAX(diameter field i,diameter field j,diameter through i and j)
			di = min(di,max(max(dii,dij),longesti+distance(i,j)+longestj));
		}
	}

	printf("%.6f\n",di);

	return 0;
}
