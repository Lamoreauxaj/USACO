/*
ID: lamorea1
LANG: C++11
PROG: humble
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

int K, N;
long long primes[110];
vector<long long> humble;
int nex[110];

//returns the index of the humble number that * primes[j] is just greater than the last humble number
int calculatenext(int j) {
	long long lim = humble[humble.size()-1];
	if(nex[j]!=-1) {
		int i = 0;
		while(nex[j]+i<humble.size()&&primes[j]*humble[nex[j]+i]<=lim) i++;
		if(nex[j]+i==humble.size()) return nex[j] = -1;
		return nex[j] = nex[j]+i;
	}
	else {
		int i = 1;
		while(nex[j]+i<humble.size()&&primes[j]*humble[nex[j]+i]<=lim) i++;
		if(nex[j]+i==humble.size()) return nex[j] = -1;
		return nex[j] = nex[j]+i;
	}
}

int main() {
	freopen("humble.in","r",stdin);
	freopen("humble.out","w",stdout);

	//take input
	scanf("%d %d",&K,&N);
	for(int i = 0; i < K; i++) scanf("%lld",&primes[i]);
	fill(nex,nex+K,-1);

	//find nex highest humble number by using the past humble numbers and attempting to multiply by each possible prime
	humble.push_back(1LL);
	for(int i = 0; i < N; i++) {
		long long smallest = 1600147000000;
		for(int j = 0; j < K; j++) {//find the min number(humble[k]*primes[j]) that is just greater than the last humble number
			int t = calculatenext(j);
			if(t==-1) continue;
			smallest = min(smallest,primes[j]*humble[t]);
		}
		humble.push_back(smallest);
	}

	printf("%lld\n",humble[N]);

	return 0;
}
