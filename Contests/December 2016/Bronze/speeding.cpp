#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
	freopen("speeding.in","r",stdin);
	freopen("speeding.out","w",stdout);

	//input
	int n, m;
	scanf("%d %d",&n,&m);
	vector<pair<pair<int,int>,int> > a(n);
	vector<pair<pair<int,int>,int> > b(m);
	int sum = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d %d",&a[i].first.second,&a[i].second);
		a[i].first.first = sum; a[i].first.second += sum;
		sum = a[i].first.second;
	}sum = 0;
	for(int i = 0; i < m; i++) {
		scanf("%d %d",&b[i].first.second,&b[i].second);
		b[i].first.first = sum; b[i].first.second += sum;
		sum = b[i].first.second;
	}

	//process
	int ans = 0;
	int i = 0;
	int j = 0;
	for(int i = 0; i < n; i++) {
		while(j < m) {
			if(b[j].first.second <= a[i].first.first) j++;
			//if these intervals overlap
			else if(max(a[i].first.first,b[j].first.first) < min(a[i].first.second,b[j].first.second))
				ans = max(ans,max(0,b[j].second - a[i].second)), j++;
			else {
				j--;
				break;
			}
		}
	}

	//output
	printf("%d\n",ans);

	return 0;
}