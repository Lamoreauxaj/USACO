/*
ID: lamorea1
LANG: C++11
PROG: kimbits
*/
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

int N, L; long long I;

//n choose r
long long ncr(int n, int r) {
	long long ret = 1;
	for(int i = 1; i <= r; i++) {
		ret*=(n+1)-i;
		ret/=i;
	}
	return ret;
}

//returns the number of possible items with size number of bits and at most bitsavail
long long include(int size, int bitsavail) {
	int ret = 0;
	for(int i = 0; i <= bitsavail; i++) ret += ncr(size,i);
	return ret;
}

//returns binary string of length N
string tostring(int n) {
	string ret;
	while(n>0) {
		ret+=to_string(n%2);
		n/=2;
	}
	while(ret.size()<N) ret+="0";
	reverse(ret.begin(), ret.end());
	return ret;
}

//prints the Ith number with size N and at most bitsavail bits (comebefore and pos and n start at 0)
void recurse(long long comebefore, int n, int pos, int bitsavail) {
	if(pos==N) {
		printf("%s\n",tostring(n).c_str());
		return;
	}
	long long left = include(N-pos-1,bitsavail);
	long long right = include(N-pos-1,bitsavail-1);
	if(left+comebefore<I) {
		recurse(left+comebefore,(n<<1)+1,pos+1,bitsavail-1);
	}else {
		recurse(comebefore,(n<<1),pos+1,bitsavail);
	}
}

int main() {
	freopen("kimbits.in","r",stdin);
	freopen("kimbits.out","w",stdout);

	scanf("%d %d %lld",&N,&L,&I);
	recurse(0,0,0,L);

	return 0;
}
