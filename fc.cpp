/*
ID: lamorea1
LANG: C++11
PROG: fc
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct vec {double x, y;
	vec() : x(0), y(0) {}
	vec(double _x, double _y) : x(_x), y(_y) {}
	vec operator -(vec other) {return vec(x-other.x,y-other.y);}
	vec operator +(vec other) {return vec(x+other.x,y+other.y);}
	double operator *(vec other) {return x*other.x+y*other.y;} //dot
	double operator ^(vec other) {return x*other.y - y*other.x;} //cross
};

bool ccw(vec p1, vec p2, vec r) {
	return ((p2-p1)^(r-p1)) > 0;
}

bool collinear(vec p1, vec p2, vec r) {
	return ((p2-p1)^(r-p1)) == 0;
}

double dist(vec a, vec b) {
	return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
}

vec pivot; //used to sort points in graham's scan
bool comp(vec a, vec b) {
	if(collinear(pivot,a,b))
		return dist(pivot,a) < dist(pivot,b);
	return atan2(a.y-pivot.y,a.x-pivot.x) < atan2(b.y-pivot.y,b.x-pivot.x);
}

//returns the convex hull of P (graham's scan algorithm)
vector<vec> CH(vector<vec> P) {
	if(P.size()<=3)
		return P;

	int P0 = 0;
	for(int i = 1; i < P.size(); i++)
		if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x < P[P0].x))
			P0 = i;
	vec t = P[0]; P[0] = P[P0]; P[P0] = t;
	pivot = P[0];
	sort(++P.begin(),P.end(),comp);

	vector<vec> S;
	S.push_back(P[0]); S.push_back(P[1]);
	int i = 2;
	while(i < P.size()) {
		if(ccw(S[S.size()-2],S[S.size()-1],P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}return S;
}

//return perimeter of polygon P
double perimeter(vector<vec> P) {
	double peri = 0;
	peri += dist(P[0],P[P.size()-1]);
	for(int i = 1; i < P.size(); i++) peri += dist(P[i-1],P[i]);
	return peri;
}

int N;
vector<vec> P;

int main() {
	freopen("fc.in","r",stdin);
	freopen("fc.out","w",stdout);

	//input
	scanf("%d",&N);
	P = vector<vec>(N,vec());
	for(int i = 0; i < N; i++) scanf("%lf %lf",&P[i].x,&P[i].y);

	P = CH(P);

	//output
	printf("%.2f\n",perimeter(P));

	return 0;
}
