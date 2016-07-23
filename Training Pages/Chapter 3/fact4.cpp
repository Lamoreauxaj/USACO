/*
ID: lamorea1
LANG: C++11
PROG: fact4
*/
#include <cstdio>
using namespace std;

int N;

int main() {
	freopen("fact4.in","r",stdin);
	freopen("fact4.out","w",stdout);

	scanf("%d",&N);

	int currdigit = 1;
	int power2 = 0;
	int power5 = 0;
	for(int i = 2; i <= N; i++) {
		int t = i; while(t%2==0) {t/=2;power2++;} while(t%5==0) {t/=5;power5++;} //remove all factors of two and five so we can never get an ending zero
		currdigit *= t;
		currdigit %= 10;
	}

	if(power2>=power5) {
		for(int i = 0; i < power2-power5; i++) { //add back the extra 2's
			currdigit*=2;
			currdigit%=10;
		}
	}else {
		for(int i = 0; i < power5-power2; i++) { //add back the extra 5's
			currdigit*=5;
			currdigit%=10;
		}
	}

	printf("%d\n",currdigit);


	return 0;
}
