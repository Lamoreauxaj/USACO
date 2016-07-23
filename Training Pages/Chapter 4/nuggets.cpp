/*
ID: lamorea1
LANG: C++11
PROG: nuggets
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

const int INTMAX = int((1<<31LL)-1);

int N;
int val[12];
int lim = 0; //used to see if all numbers are now creatable which happens if there are lim creatable in a row
vector<int> nums;
int nex[12];

//returns the item which when added with j is just greater than the maximum so far 
int calculatenex(int j) {
	while(nums[nex[j]]+val[j]<=nums[nums.size()-1]) nex[j]++;
	return nex[j];
}

int main() {
	// int start = clock();
	freopen("nuggets.in","r",stdin);
	freopen("nuggets.out","w",stdout);

	//input
	scanf("%d",&N);
	for(int i = 0; i < N&&scanf("%d",&val[i]); i++) lim = max(lim,val[i]);

	//process
	nums.push_back(0);
	fill(nex,nex+N,0);
	int last = 0;
	while(nums[nums.size()-1]-last<=lim&&last<=65024) { //while haven't found largest and largest can still exist
		int mini = INTMAX;
		for(int j = 0; j < N; j++) mini = min(mini,nums[calculatenex(j)]+val[j]); //find minimum that is just greater than max so far
		if(mini-nums[nums.size()-1]!=1) last = mini-1; //if we skipped a number that can't be made put it in last
		nums.push_back(mini);
	}

	if(last>65024) printf("%d\n",0); //largest doesn't exist
	else printf("%d\n",last);

	return 0;
}
