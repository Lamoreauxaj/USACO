/*
ID: lamorea1
LANG: C++11
PROG: zerosum
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
ifstream in("zerosum.in");
ofstream out("zerosum.out");

int N;
vector<string> ans;

//recursively generate all possible equations
void recurse(int sum, int pos, string eq) {
	if(pos>N) {
		if(sum==0)
		ans.push_back(eq);
		return;
	}

	int term = 0;
	string term_str = "";
	while(pos<=N) { //try taking all possible next numbers pos, pos*10 + pos+1, pos*100 + (pos+1)*10 + pos+2, etc
		term = term*10+pos;
		term_str+=" "+to_string(pos);
		if(pos-term_str.size()/2==0) recurse(term,pos+1,term_str.substr(1,term_str.size()-1)); //first call to this function (no leading plus/minus)
		else {
			recurse(sum+term,pos+1,eq+"+"+term_str.substr(1,term_str.size()-1)); //substr to get rid of extra space
			recurse(sum-term,pos+1,eq+"-"+term_str.substr(1,term_str.size()-1)); //try recursively both ways of adding or subtracting the next term
		}
		pos++;
	}
}


int main() {

	//take input
	in >> N;

	recurse(0,1,"");

	//print output
	sort(ans.begin(),ans.end());

	for(int i = 0; i < ans.size(); i++) {
		out << ans[i] << '\n';
	}

	return 0;
}
