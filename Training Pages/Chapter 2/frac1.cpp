/*
ID: lamorea1
LANG: C++
PROG: frac1
*/
#include <cstdio>
#include <algorithm>
using namespace std;

//returns greatest common divisor of a and b
int gcd(int a, int b) {
	while(a*b>0) {
		int r = a;
		a = b%a;
		b = r;
	}return a+b;
}

struct Frac {
	int n, d;
	Frac() {}
	Frac(int num, int den) {n = num; d = den;}
	void simplify() {int gc = gcd(n,d); n/=gc; d/=gc;}
	bool operator <(Frac other) const {return n/double(d) < other.n/double(other.d);}
	bool operator !=(Frac other) const {return !(n==other.n&&d==other.d);}
};

int N;
Frac fracs[25600];
int num_fracs = 0;

int main() {
	freopen("frac1.in","r",stdin);
	freopen("frac1.out","w",stdout);

	//take input
	scanf("%d",&N);

	//create fractions
	fracs[num_fracs++] = Frac(0,1); fracs[num_fracs++] = Frac(1,1); 
	for(int d = 2; d <= N; d++) {
		for(int n = 1; n < d; n++) {
			fracs[num_fracs] = Frac(n,d);
			fracs[num_fracs++].simplify();
		}
	}

	sort(fracs,fracs+num_fracs);

	//print all distinct fracs
	printf("%d/%d\n",fracs[0].n,fracs[0].d);
	for(int i = 1; i < num_fracs; i++) {
		if(fracs[i]!=fracs[i-1]) {
			printf("%d/%d\n",fracs[i].n,fracs[i].d);
		}
	}

	return 0;
}
