/*
ID: lamorea1
LANG: C++11
PROG: buylow
*/
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <map>
using namespace std;

struct bigint {
	int num[1000];
	bigint() {
		for(int i = 0; i < 1000; i++) num[i] = 0;
	}
	char* c_str() {
		char* temp = new char[1000];
		for(int i = 0; i < 1000; i++) temp[i] = num[i]+'0';
		int i;
		for(i = 999; i >= 0&&temp[i]=='0'; i--) ;
		temp[i+1] = '\0';
		reverse(temp,temp+i+1);
		return temp;
	}
	void operator +=(bigint other) {
		int carry = 0;
		for(int i = 0; i < 1000; i++) {
			num[i] = num[i] + other.num[i] + carry;
			if(num[i]>=10) {
				num[i] %= 10;
				carry = 1;
			}else {
				carry = 0;
			}
		}
	}
	void operator +=(int other) {
		int carry = 0;
		for(int i = 0; i < 1000; i++) {
			num[i] = num[i] + other%10 + carry;
			if(num[i]>=10) {
				num[i] %= 10;
				carry = 1;
			}else {
				carry = 0;
			}
			other/=10;
		}
	}
};

int N;
int price[5000];
int memo[5000];

map<pair<int,pair<int,int>>,bigint> memo1;

bigint countseq(int len, int pos, int minprice) {//returns number of sequences that have len len, end before pos, and all have prices greater than minprice
	if(memo1.count(pair<int,pair<int,int>>(len,pair<int,int>(pos,minprice)))) return memo1[pair<int,pair<int,int>>(len,pair<int,int>(pos,minprice))];
	bigint total;
	unordered_set<int> seen;
	for(int i = pos-1; i >= 0; i--) {
		if(memo[i]!=len) continue;
		if(seen.count(price[i])) continue;
		if(price[i] <= minprice) continue;
		seen.insert(price[i]);
		if(len>1)
			total+=countseq(len-1,i,price[i]);
		else total+=1;
	}
	return memo1[pair<int,pair<int,int>>(len,pair<int,int>(pos,minprice))] = total;
}

int main() {
	freopen("buylow.in","r",stdin);
	freopen("buylow.out","w",stdout);

	//input
	scanf("%d",&N);
	for(int i = 0; i < N; i++) scanf("%d",&price[i]);
	fill(memo,memo+N,1);

	//preform iterative dp
	for(int i = 1; i < N; i++)
		for(int j = 0; j < i; j++)
			if(price[j] > price[i])
				memo[i] = max(memo[i],memo[j]+1);

	//find max length
	int maxi = 0;
	for(int i = 0; i < N; i++) maxi = max(maxi,memo[i]);

	printf("%d %s\n",maxi,countseq(maxi,N,-1).c_str());
	return 0;
}
