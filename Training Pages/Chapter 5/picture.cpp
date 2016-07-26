/*
ID: lamorea1
LANG: C++11
PROG: picture
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int N;

//runs a 1d sweep to calculate the number of open spots in the interval
int oneDSweep(map<pair<int,bool>,int> &bst) {
	int count = 0; //number of segments currently over
	int total = 0; //number of end points of the union of these segments
	for(pair<pair<int,bool>,int> i : bst) {
		if(count == 0) { if(!i.first.second) total++;
		}else if(count - i .second == 0) if(i.first.second) total++;
		if(i.first.second) count-=i.second; else count+=i.second;
	}
	return total;
}

//removes or adds an item from our bst (we have to use a map because the possibility of degenerate lines that overlap)
void update(pair<int,bool> a, map<pair<int,bool>,int>& bst, int up) {
	if(!bst.count(a)) bst[a] = 0;
	bst[a] += up;
	if(bst[a] == 0) bst.erase(a);
}

int main() {
	freopen("picture.in","r",stdin);
	freopen("picture.out","w",stdout);

	//input
	scanf("%d",&N);int x, y, x1, y1;
	vector<pair<int,pair<bool,pair<int,int>>>> xarr;
	vector<pair<int,pair<bool,pair<int,int>>>> yarr;
	for(int i = 0; i < N; i++) {
		scanf("%d %d %d %d",&x,&y,&x1,&y1);
		if(x > x1) {int t = x1;x1 = x;x = t;}
		if(y > y1) {int t = y1;y1 = y;y = t;}
		xarr.push_back(pair<int,pair<bool,pair<int,int>>>(x,pair<bool,pair<int,int>>(true,pair<int,int>(y,y1))));
		xarr.push_back(pair<int,pair<bool,pair<int,int>>>(x1,pair<bool,pair<int,int>>(false,pair<int,int>(y,y1))));
		yarr.push_back(pair<int,pair<bool,pair<int,int>>>(y,pair<bool,pair<int,int>>(true,pair<int,int>(x,x1))));
		yarr.push_back(pair<int,pair<bool,pair<int,int>>>(y1,pair<bool,pair<int,int>>(false,pair<int,int>(x,x1))));
	}
	sort(xarr.begin(),xarr.end());
	sort(yarr.begin(),yarr.end());

	//run a sweep line vertically and horizontally counting the perimeter
	int peri = 0;
	map<pair<int,bool>,int> bst;
	int last = xarr[0].first;
	for(int i = 0; i < xarr.size(); i++) {
		pair<int,pair<bool,pair<int,int>>> temp = xarr[i];
		if(i == 0 || temp.first != xarr[i-1].first) {
			peri += (temp.first - last) * oneDSweep(bst);
			last = temp.first;
		}
		if(!temp.second.first) update(pair<int,bool>(temp.second.second.first,false),bst,-1), update(pair<int,bool>(temp.second.second.second,true),bst,-1);
		else update(pair<int,bool>(temp.second.second.first,false),bst,1), update(pair<int,bool>(temp.second.second.second,true),bst,1);
	}
	bst.clear();
	last = yarr[0].first;
	for(int i = 0; i < yarr.size(); i++) {
		pair<int,pair<bool,pair<int,int>>> temp = yarr[i];
		if(i == 0 || temp.first != yarr[i-1].first) {
			peri += (temp.first - last) * oneDSweep(bst);
			last = temp.first;
		}
		if(!temp.second.first) update(pair<int,bool>(temp.second.second.first,false),bst,-1), update(pair<int,bool>(temp.second.second.second,true),bst,-1);
		else update(pair<int,bool>(temp.second.second.first,false),bst,1), update(pair<int,bool>(temp.second.second.second,true),bst,1);
	}

	//output
	printf("%d\n",peri);

	return 0;
}
