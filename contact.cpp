/*
ID: lamorea1
LANG: C++11
PROG: contact
*/
#include <cstdio>
#include <vector>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct comp {
	bool operator() (pair<int,pair<int,int>> a, pair<int,pair<int,int>> b) {
		if(a.first==b.first) {
			if(a.second.first==b.second.first) {
				return a.second.second < b.second.second;
			}return a.second.first < b.second.first;
		}
		return a.first > b.first;
	}
};

string tostring(pair<int,int> lv) { //turns lv into a lv.first length binary string with value of lv.second
	int n = lv.second; int len = lv.first;
	string ret;
	while(n>0) {
		ret+=char(n%2+'0');
		n/=2;
	}
	while(ret.size()<len) ret+="0";
	reverse(ret.begin(), ret.end());
	return ret;
}

int A, B, N;
string line;
map<pair<int,int>,int> loc; //stores where (len,val) is in freq so we can update it
vector<pair<int,pair<int,int>>> freq; //stores (freq, (len,val)) //used to sort them after instead of just incrementing them in the map


int main() {
	freopen("contact.in","r",stdin);
	freopen("contact.out","w",stdout);

	//take input
	scanf("%d %d %d",&A,&B,&N);
	char temp[100];
	while(scanf("%s",temp)!=EOF) line+=temp;

	//process by hashing the strings into binary numbers (rolling hash)
	int val = 0; //stores last 15 characaters binary value
	for(int i = 0; i < line.size(); i++) {
		val = (val<<1)+line[i]-'0';
		val %= (1<<15);
		for(int j = A; j <= B&&j<=i+1; j++) {
			pair<int,int> t(j,val%(1<<j)); //val of the last j bits
			if(loc.count(t)) {
				freq[loc[t]].first += 1;
			}else {
				loc[t] = freq.size();
				freq.push_back(pair<int,pair<int,int>>(1,t));
			}
		}
	}

	//print out the N highest freqs
	sort(freq.begin(),freq.end(),comp());
	int count = 1, found = 0;
	for(int i = 1; i < freq.size()&&found<N; i++) {
		if(freq[i].first!=freq[i-1].first) { //end of a chain of equal freq
			printf("%d\n",freq[i-1].first);
			for(int j = 0; j+(i-count) < i; j++) {
				if(j%6==0&&j>0) printf("\n");
				if(j%6==0)
					printf("%s",tostring(freq[j+(i-count)].second).c_str());
				else printf(" %s",tostring(freq[j+(i-count)].second).c_str());
			}
			printf("\n");
			found++;
			count = 1;
		}else {
			count++;
		}
	}
	if(found<N) { //if we didn't find enough we just have to print out whatever was left
		printf("%d\n",freq[freq.size()-1].first);
		printf("%s",tostring(freq[freq.size()-count].second).c_str());
		for(int j = freq.size()-count+1; j < freq.size(); j++)
			printf(" %s",tostring(freq[j].second).c_str());
		printf("\n");
	}

	return 0;
}
