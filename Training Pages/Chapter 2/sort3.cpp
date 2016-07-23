/*
ID: lamorea1
LANG: C++
PROG: sort3
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	freopen("sort3.in","r",stdin);
	freopen("sort3.out","w",stdout);

	int N; int num[] = {0,0,0}; int num_in_threes[] = {0,0,0}; int num_in_twos[] = {0,0,0}; int num_in_ones[] = {0,0,0}; 
	int nums[1010];

	//take input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) scanf("%d",&nums[i]);
	
	//instantiate num array
	for(int i = 0; i < N; i++) {
		switch(nums[i]) {
			case 1:
			num[0]++;
			break;
			case 2:
			num[1]++;
			break;
			case 3:
			num[2]++;
			break;
		}
	}

	//initialize num_in arrays
	for(int i = 0; i < N; i++) {
		if(i<num[0]) {
			switch(nums[i]) {
				case 2:
				num_in_ones[1]++;
				break;
				case 3:
				num_in_ones[2]++;
				break;
			}
		}else if(i<num[1]+num[0]) {
			switch(nums[i]) {
				case 1:
				num_in_twos[0]++;
				break;
				case 3:
				num_in_twos[2]++;
				break;
			}
		}else {
			switch(nums[i]) {
				case 1:
				num_in_threes[0]++;
				break;
				case 2:
				num_in_threes[1]++;
				break;
			}
		}
	}

	int total = 0;

	//try swaping twos in threes with threes in twos
	int m = min(num_in_threes[1],num_in_twos[2]);
	total+=m;
	num_in_threes[1] -= m; num_in_twos[2] -= m;

	//try swapping ones in threes with threes in ones
	m = min(num_in_threes[0],num_in_ones[2]);
	total+=m;
	num_in_threes[0] -= m; num_in_ones[2] -= m;

	//try swapping ones in twos with twos in ones
	m = min(num_in_twos[0],num_in_ones[1]);
	total+=m;
	num_in_twos[0] -= m; num_in_ones[1] -= m;

	//try swapping triplits
	total+=max(num_in_twos[0],num_in_twos[2])*2;

	printf("%d\n",total);

	return 0;
}
