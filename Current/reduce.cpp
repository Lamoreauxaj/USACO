/*
ID: lamorea1
LANG: C++!1
PROG: reduce
*/
#include <cstdio>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <vector>
using namespace std;

int N;
pair<int,int> points[50000];

vector<int> findminx() {
	priority_queue<int> pq;
	for(int i = 0; i < N; i++) {
		pq.push(-points[i].first);
	}
	vector<int> ret;
	for(int i = 0; i < 4; i++) {
		if(pq.size()>0) ret.push_back(-pq.top()), pq.pop();
	}
	return ret;
}
vector<int> findminy() {
	priority_queue<int> pq;
	for(int i = 0; i < N; i++) {
		pq.push(-points[i].second);
	}
	vector<int> ret;
	for(int i = 0; i < 4; i++) {
		if(pq.size()>0) ret.push_back(-pq.top()), pq.pop();
	}
	return ret;
}
vector<int> findmaxx() {
	priority_queue<int> pq;
	for(int i = 0; i < N; i++) {
		pq.push(points[i].first);
	}
	vector<int> ret;
	for(int i = 0; i < 4; i++) {
		if(pq.size()>0) ret.push_back(pq.top()), pq.pop();
	}
	return ret;
}
vector<int> findmaxy() {
	priority_queue<int> pq;
	for(int i = 0; i < N; i++) {
		pq.push(points[i].second);
	}
	vector<int> ret;
	for(int i = 0; i < 4; i++) {
		if(pq.size()>0) ret.push_back(pq.top()), pq.pop();
	}
	return ret;
}

// vector<int> findminx(unordered_set<int> &ign) {
// 	int minim = 1000000000;
// 	vector<int> best;
// 	for(int i = 0; i < N; i++) { if(ign.count(i)) continue;
// 		if(points[i].first < minim) {
// 			minim = points[i].first;
// 			best.clear();
// 		}
// 		if(points[i].first==minim) best.push_back(i);
// 	}
// 	int mini = 1000000000;
// 	int maxi = 0;
// 	vector<int> ret;
// 	for(int i = 0; i < best.size(); i++) maxi = max(maxi,points[best[i]].second), mini = min(mini,points[best[i]].second);
// 	for(int i = 0; i < best.size(); i++) if(points[best[i]].second==maxi&&points[best[i]].second==mini) ret.push_back(best[i]);
// 	return ret;
// }
// vector<int> findminy(unordered_set<int> &ign) {
// 	int minim = 1000000000;
// 	vector<int> best;
// 	for(int i = 0; i < N; i++) { if(ign.count(i)) continue;
// 		if(points[i].second < minim) {
// 			minim = points[i].second;
// 			best.clear();
// 		}
// 		if(points[i].second==minim) best.push_back(i);
// 	}
// 	int mini = 1000000000;
// 	int maxi = 0;
// 	vector<int> ret;
// 	for(int i = 0; i < best.size(); i++) maxi = max(maxi,points[best[i]].first), mini = min(mini,points[best[i]].first);
// 	for(int i = 0; i < best.size(); i++) if(points[best[i]].first==maxi&&points[best[i]].first==mini) ret.push_back(best[i]);
// 	return ret;
// }
// vector<int> findmaxx(unordered_set<int> &ign) {
// 	int minim = 0;
// 	vector<int> best;
// 	for(int i = 0; i < N; i++) { if(ign.count(i)) continue;
// 		if(points[i].first > minim) {
// 			minim = points[i].first;
// 			best.clear();
// 		}
// 		if(points[i].first==minim) best.push_back(i);
// 	}
// 	int mini = 1000000000;
// 	int maxi = 0;
// 	vector<int> ret;
// 	for(int i = 0; i < best.size(); i++) maxi = max(maxi,points[best[i]].second), mini = min(mini,points[best[i]].second);
// 	for(int i = 0; i < best.size(); i++) if(points[best[i]].second==maxi&&points[best[i]].second==mini) ret.push_back(best[i]);
// 	return ret;
// }
// vector<int> findmaxy(unordered_set<int> &ign) {
// 	int minim = 0;
// 	vector<int> best;
// 	for(int i = 0; i < N; i++) { if(ign.count(i)) continue;
// 		if(points[i].second > minim) {
// 			minim = points[i].second;
// 			best.clear();
// 		}
// 		if(points[i].second==minim) best.push_back(i);
// 	}
// 	int mini = 1000000000;
// 	int maxi = 0;
// 	vector<int> ret;
// 	for(int i = 0; i < best.size(); i++) maxi = max(maxi,points[best[i]].first), mini = min(mini,points[best[i]].first);
// 	for(int i = 0; i < best.size(); i++) if(points[best[i]].first==maxi&&points[best[i]].first==mini) ret.push_back(best[i]);
// 	return ret;
// }

// int recurse(int pos, unordered_set<int> ign) {//returns the minimum area possible that surrounds all points after removing at most 3
// 	if(pos==3) {
// 		return (points[findmaxx(ign)[0]].first - points[findminx(ign)[0]].first) * (points[findmaxy(ign)[0]].second - points[findminy(ign)[0]].second);
// 	}
// 	int mini = 1000000000;
// 	vector<int> minx = findminx(ign);
// 	for(int i = 0; i < minx.size(); i++) {
// 		unordered_set<int> pass = ign;
// 		pass.insert(minx[i]);
// 		mini = min(mini,recurse(pos+1,pass));
// 	}
// 	vector<int> maxx = findmaxx(ign);
// 	for(int i = 0; i < maxx.size(); i++) {
// 		unordered_set<int> pass = ign;
// 		pass.insert(maxx[i]);
// 		mini = min(mini,recurse(pos+1,pass));
// 	}
// 	vector<int> miny = findminy(ign);
// 	for(int i = 0; i < miny.size(); i++) {
// 		unordered_set<int> pass = ign;
// 		pass.insert(miny[i]);
// 		mini = min(mini,recurse(pos+1,pass));
// 	}
// 	vector<int> maxy = findmaxy(ign);
// 	for(int i = 0; i < maxy.size(); i++) {
// 		unordered_set<int> pass = ign;
// 		pass.insert(maxy[i]);
// 		mini = min(mini,recurse(pos+1,pass));
// 	}
// 	return mini;
// }

int main() {
	freopen("reduce.in","r",stdin);
	freopen("reduce.out","w",stdout);

	//input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) scanf("%d %d",&points[i].first,&points[i].second);

	//output
	vector<int> minx = findminx();
	vector<int> maxx = findmaxx();
	vector<int> miny = findminy();
	vector<int> maxy = findmaxy();

	vector<int> removed;
	for(int i = 0; i < minx.size(); i++) {
		removed.push_back(minx[i]);
		for(int j = 0; j < maxx.size(); j++) {
			for(int k = 0; k < miny.size(); k++) {
				for(int m = 0; m < maxy.size(); m++) {

				}
			}
		}
	}

	return 0;
}