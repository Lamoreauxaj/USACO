/*
ID: lamorea1
LANG: C++
PROG: sprime
*/
#include <cstdio>
using namespace std;

int N;
int primes[10000];
int num_primes = 0;

void sieve() {
	bool a[10001]; primes[num_primes++] = 2;
	for(int i = 3; i <= 10000; i+=2) {
		if(a[i]) continue;
		primes[num_primes++] = i;
		for(int j = i*i; j <= 10000; j+=i)
			a[j] = true;
	}
}

bool isPrime(int n) {
	for(int i = 0; i < num_primes; i++) {
		if(primes[i]*primes[i]>n) break;
		if(n%primes[i]==0) return false;
	}return true;
}

//recursively creates all primeribs
void generate(int num, int n) {
	if(!isPrime(num)) return;
	if(n==N) {
		printf("%d\n",num);
		return;
	}
	for(int d = 1; d <= 9; d+=2) {
		generate(num*10+d,n+1);
	}
}

int main() {
	freopen("sprime.in","r",stdin);
	freopen("sprime.out","w",stdout);

	scanf("%d",&N);
	sieve();

	generate(2,1);
	generate(3,1);
	generate(5,1);
	generate(7,1);

	return 0;
}
