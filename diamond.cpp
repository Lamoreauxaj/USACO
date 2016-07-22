/*
ID: lamorea1
LANG: C++11
PROG: diamond
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N, K;
int nums[50000];
pair<int,int> avail[50000];

int main() {
	freopen("diamond.in","r",stdin);
	freopen("diamond.out","w",stdout);

	//input
	scanf("%d %d",&N,&K);
	for(int i = 0; i < N; i++) {
		scanf("%d",&nums[i]);
	}
	sort(nums,nums+N);

	//process avail array (number of items that can maximum be in this case if the smallest item is at i)
	for(int i = 0; i < N; i++) {
		int pos = i+1;
		while(pos < N && nums[pos] - nums[i] <= K) pos++;
		avail[i] = pair<int,int>(pos-i,i);
	}

	//find maximum possible combination
	int ans = 0;
	sort(avail,avail+N);
	for(int i = N-1; i >= 0&&i >= N-15000; i--) {
		for(int j = i-1; j >= 0&& j>= N-15000; j--) {
			if ( avail[i].second < avail[j].second) {
				ans = max(ans, avail[j].first+min(avail[i].first,avail[j].second-avail[i].second) );
			}else if(avail[i].second > avail[j].second) {
				ans = max(ans, avail[i].first+min(avail[j].first,avail[i].second-avail[j].second) );
			}
		}
	}

	//output
	printf("%d\n",ans);

	return 0;
}
