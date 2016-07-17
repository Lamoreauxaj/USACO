/*
ID: lamorea1
LANG: C++11
PROG: theme
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int notes[5000];

int main() {
	freopen("theme.in","r",stdin);
	freopen("theme.out","w",stdout);

	//input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) scanf("%d",&notes[i]);

	//process
	int ans = 0;
	for(int i = 5; i < N; i++) {
		int len = 0;
		int dis = 2000000000;
		for(int j = 0; j < i; j++) {
			if(notes[i+len]-notes[j]==dis) {
				len++;
				if(len>=5) ans = max(ans,len);
			}else {
				len = 1;
				dis = notes[i]-notes[j];
			}
		}
	}

	//output
	printf("%d\n",ans);

	return 0;
}
