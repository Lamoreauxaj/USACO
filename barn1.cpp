/*
ID: lamorea1
LANG: C++
PROG: barn1
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int max_boards, num_stalls, num_occupied;
vector<pair<int,int> > arr;
struct comp {
	bool operator()(pair<int,int> a, pair<int,int> b) { return a.first < b.first; }
};

int main() {
	freopen("barn1.in","r",stdin);
	freopen("barn1.out","w",stdout);

	//take input
	scanf("%d %d %d",&max_boards,&num_stalls,&num_occupied);
	for(int i = 0; i < num_occupied; i++) {int loc; scanf("%d",&loc);
		arr.push_back(pair<int,int>(loc,loc));
	}
	sort(arr.begin(),arr.end(),comp());

	//perform merges on the closest items and put them under one board
	int numboards = num_occupied, length = num_occupied;
	while(numboards>max_boards) { //while adjacent boards still need to be made into one board
		//find min dist between two boards
		int mindist = 500000;
		int minloc = 0;
		for(int i = 1; i < arr.size(); i++) {
			int dist = arr[i].first-arr[i-1].second;
			if(dist<mindist) { mindist = dist; minloc = i; }
		}
		//merge the items at minloc
		numboards--; length+=mindist-1;
		arr[minloc-1].second = arr[minloc].second;
		arr.erase(arr.begin()+minloc);
	}

	printf("%d\n",length);

	return 0;
}
