/*
ID: lamorea1
LANG: C++
PROG: pprime
*/
#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;

int primes[100000];
int num_primes = 0;

//sieve of eratothemsensdasd
void sieve() {
	bool* a = new bool[10001]; primes[num_primes++] = 2;
	for(int i = 3; i <= 10000; i+=2) {
		if(a[i]) continue;
		primes[num_primes++] = i;
		for(int j = i+i; j <= 10000; j+=i)
			a[j] = true;
	}
}

bool isPrime(int n) {
	for(int i = 0; i < num_primes; i++) {
		if(primes[i]*primes[i]>n) break;
		if(n%primes[i]==0) return false;
	}return true;
}

int main() {
	freopen("pprime.in","r",stdin);
	freopen("pprime.out","w",stdout);

	//take input
	int num, a, b;
	scanf("%d %d",&a,&b);
	sieve();

	//generate palindromes and check if prime
	for(int d1 = 1; d1 < 10; d1+=2) {
		num = d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}
	for(int d1 = 1; d1 < 10; d1+=2) {
		num = d1*10+d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}
	for(int d1 = 1; d1 < 10; d1+=2)
	for(int d2 = 0; d2 < 10; d2++) {
		num = d1*100+d2*10+d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}
	for(int d1 = 1; d1 < 10; d1+=2)
	for(int d2 = 0; d2 < 10; d2++) {
		num = d1*1000+d2*100+d2*10+d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}
	for(int d1 = 1; d1 < 10; d1+=2)
	for(int d2 = 0; d2 < 10; d2++)
	for(int d3 = 0; d3 < 10; d3++) {
		num = d1*10000+d2*1000+d3*100+d2*10+d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}
	for(int d1 = 1; d1 < 10; d1+=2)
	for(int d2 = 0; d2 < 10; d2++)
	for(int d3 = 0; d3 < 10; d3++) {
		num = d1*100000+d2*10000+d3*1000+d3*100+d2*10+d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}
	for(int d1 = 1; d1 < 10; d1+=2)
	for(int d2 = 0; d2 < 10; d2++)
	for(int d3 = 0; d3 < 10; d3++)
	for(int d4 = 0; d4 < 10; d4++) {
		num = d1*1000000+d2*100000+d3*10000+d4*1000+d3*100+d2*10+d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}
	for(int d1 = 1; d1 < 10; d1+=2)
	for(int d2 = 0; d2 < 10; d2++)
	for(int d3 = 0; d3 < 10; d3++)
	for(int d4 = 0; d4 < 10; d4++) {
		num = d1*10000000+d2*1000000+d3*100000+d4*10000+d4*1000+d3*100+d2*10+d1; if(num<a||num>b) continue;
		if(isPrime(num))
			printf("%d\n",num);
	}

	return 0;
}
