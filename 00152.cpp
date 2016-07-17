#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

struct vec3 {double x, y, z;
	vec3() : x(0.0), y(0.0), z(0.0) {}
	vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
};

double dist(vec3 a, vec3 b) {
	return sqrt((pow(a.x-b.x,2) + pow(a.y-b.y,2)) + pow(a.z-b.z,2));
}

vector<vec3> trees;
vector<int> ans(10,0);

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	//input
	int x,y,z;
	while(scanf("%d %d %d",&x,&y,&z)&&(x||y||z)) {
		trees.push_back(vec3(x,y,z));
	}

	//process
	for(int i = 0; i < trees.size(); i++) {
		double mini = 1000000000;
		for(int j = 0; j < trees.size(); j++) {if(i==j) continue;
			double d = dist(trees[i],trees[j]);
			mini = min(mini,d);
		}
		if(int(mini)<=9)
			ans[int(mini)]++;
	}

	//output
	for(int i = 0; i < 10; i++) {
		printf("%4d",ans[i]);
	}printf("\n");

	return 0;
}
