/*
ID: lamorea1
LANG: C++
PROG: hamming
*/
#include <cstdio>
using namespace std;

int N, B, D;
int nums[70];
int num_found = 0;

//returns hamming dist of two nums
int hamming_dist(int a, int b) {
	int dist = a ^ b;
	int count = 0;
	for(int i = 0; i < B; i++) if(dist&(1<<i)) count++;
	return count;
}

//returns true if n is at least D dist away from all past nums
bool valid(int n) {
	for(int i = 0; i < num_found; i++) {
		if(hamming_dist(nums[i],n)<D) return false;
	}return true;
}

int main() {
	freopen("hamming.in","r",stdin);
	freopen("hamming.out","w",stdout);

	//take input
	scanf("%d %d %d",&N,&B,&D);
	nums[num_found++] = 0; N--;

	for(int i = 1; N>0	; i++) { // while N items have not been found
		if(valid(i)) {
			nums[num_found++] = i;
			N--;
		}
	}

	//print output
	printf("%d",nums[0]);
	for(int i = 1; i < num_found; i++) {
		if(i%10==0) {
			printf("\n");
			printf("%d",nums[i]);
		}
		else
			printf(" %d",nums[i]); 

	}printf("\n");

	return 0;
}
