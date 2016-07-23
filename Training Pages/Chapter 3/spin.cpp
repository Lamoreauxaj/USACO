/*
ID: lamorea1
LANG: C++11
PROG: spin
*/
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

struct Wheel {
	int pos;
	int speed;
	int W;
	pair<int,int> wedges[5];
	bool open[360];
};

Wheel wheels[5];

Wheel wheel() {
	Wheel ret;
	ret.pos = 0;
	scanf("%d %d",&ret.speed,&ret.W);
	for(int i = 0; i < ret.W; i++) {
		scanf("%d %d",&ret.wedges[i].first,&ret.wedges[i].second);
	}
	fill(ret.open,ret.open+360,false);
	for(int i = 0; i < ret.W; i++) {
		for(int j = ret.wedges[i].first; j <= ret.wedges[i].first+ret.wedges[i].second; j++) {
			ret.open[j%360] = true;
		}
	}
	return ret;
}

void inc() {//updates wheels as if a second had just passed
	for(int i = 0; i < 5; i++) wheels[i].pos = ( (wheels[i].pos - wheels[i].speed) % 360 + 360 ) % 360;
}

bool check() {//checks if there is a open spot on all the wheels in their current position
	for(int i = 0; i < 360; i++) { int j;
		for(j = 0; j < 5; j++) {
			if( !wheels[j].open[ ( ( i + wheels[j].pos ) % 360 + 360 ) % 360 ] ) break;
		}
		if(j==5) return true;
	}
	return false;
}

int main() {
	freopen("spin.in","r",stdin);
	freopen("spin.out","w",stdout);

	//init wheels
	for(int i = 0; i < 5; i++) wheels[i] = wheel();

	//run until all 5 wheels line up with an opening between all of them
	int count = 0;
	while(count<50000) {
		if(check()) {
			printf("%d\n",count);
			break;
		}
		inc();
		count++;
	}

	if(count==50000) printf("none\n");



	return 0;
}
