/*
ID: lamorea1
LANG: C++
PROG: lamps
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int N, C;
vector<int> on;
vector<int> off;
vector<int> ans;

//turns it into a binary string of length 6
string tostring(int n) {
	string ret; ret.reserve(250);
	while(n>0) {
		ret+=n%2+'0';
		n/=2;
	}
	while(ret.size()<6) ret+='0';
	reverse(ret.begin(),ret.end());

	//append itself
	while(ret.size()<N) ret+=ret;
	return ret.substr(0,N);
}

//count number of bits on in n
int bitcount(int n) {
	int count = 0;
	for(int i = 0; i < 4; i++) if(n&(1<<i)) count++;
	return count;
}

//returns the bitmask that corresponds to this sequence of button presses
int operate(int config) {
	int bitmask = (1<<6)-1;
	if(config&1) {
		for(int i = 1; i <= 6; i++) bitmask^=(1<<(6-i));
	}if(config&2) {
		for(int i = 1; i <= 6; i+=2) bitmask^=(1<<(6-i));
	}if(config&4) {
		for(int i = 2; i <= 6; i+=2) bitmask^=(1<<(6-i));
	}if(config&8) {
		for(int i = 1; i <= 6; i+=3) bitmask^=(1<<(6-i));
	}
	return bitmask;
}

//checks if a bitmask is a valid configuration
bool isvalid(int n) {
	for(int i = 0; i < on.size(); i++) if(!(n&(1<<(6-on[i])))) return false;
	for(int i = 0; i < off.size(); i++) if(n&(1<<(6-off[i]))) return false;
	return true;
}

int main() {
	freopen("lamps.in","r",stdin);
	freopen("lamps.out","w",stdout);

	//take input
	scanf("%d %d",&N,&C);
	int t;
	while(scanf("%d",&t)&&t!=-1) on.push_back((t-1)%6+1);
	while(scanf("%d",&t)&&t!=-1) off.push_back((t-1)%6+1);

	//try all valid series of button presses
	for(int config = 0; config < (1<<4); config++) {
		int bitc = bitcount(config);
		if(bitc<=C&&bitc%2==C%2) {
			ans.push_back(operate(config));
		}
	}

	//sort and then print
	sort(ans.begin(),ans.end());

	bool none = true;
	for(int i = 0; i < ans.size(); i++) {
		if(!isvalid(ans[i])) continue;
		printf("%s\n",tostring(ans[i]).c_str());
		none = false;
	}

	if(none) printf("IMPOSSIBLE\n");

	return 0;
}
