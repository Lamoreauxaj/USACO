#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);

	//input
	vector<pair<int,int>> points(2);
	scanf("%d %d %d %d",&points[0].first,&points[0].second,&points[1].first,&points[1].second);

	//merge overlapping points
	sort(points.begin(),points.end());
	for(int i = 0; i < points.size()-1; i++) {
		if(points[i].second >= points[i+1].first) {
			points[i] = pair<int,int>(points[i].first,max(points[i+1].second,points[i].second));
			points.erase(points.begin()+i+1);
			i--;
		}
	}

	//output
	int ans = 0;
	for(int i = 0; i < points.size(); i++) {
		ans += points[i].second - points[i].first;
	}
	printf("%d\n",ans);


	return 0;
}