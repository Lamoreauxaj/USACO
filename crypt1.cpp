/*
ID: lamorea1
LANG: C++
PROG: crypt1
*/
#include <cstdio>
#include <set>
using namespace std;

int N;
set<int> digits;

//checks if these 5 digits create a valid solution
bool isvalid(int a, int b, int c, int d, int e) {
	if(!digits.count(a)||!digits.count(b)||!digits.count(c)||!digits.count(d)||!digits.count(e)) return false;
	int abc = a*100+b*10+c;
	int part1 = e*abc;
	if(part1>=1000) return false;
	int part2 = d*abc;
	if(part2>=1000) return false;
	int final = abc*(d*10+e);
	if(final>=10000) return false;

	//check if all digits in partial products and the answer come from the digits set
	while(part1>0) {
		if(!digits.count(part1%10)) return false;
		part1/=10;
	}while(part2>0) {
		if(!digits.count(part2%10)) return false;
		part2/=10;
	}while(final>0) {
		if(!digits.count(final%10)) return false;
		final/=10;
	}
	return true;
}

int main() {
	freopen("crypt1.in","r",stdin);
	freopen("crypt1.out","w",stdout);

	//take input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) {
		int digit; scanf("%d",&digit); digits.insert(digit);
	}

	//try all permutations of digits a,b,c,d,e
	int count = 0;
	for(int a = 1; a < 10; a++)
		for(int b = 1; b < 10; b++)
			for(int c = 1; c < 10; c++)
				for(int d = 1; d < 10; d++)
					for(int e = 1; e < 10; e++)
						if(isvalid(a,b,c,d,e)) {
							count++;
						}



	printf("%d\n",count);


	return 0;
}
