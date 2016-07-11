/*
ID: lamorea1
LANG: C++11
PROG: prefix
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_set>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int memo[200020];
unordered_set<string> prims;
string S;

//returns the longest prefix in S creatable from items within prims
int count(int pos) {
	if(pos>=S.size()) return 0;
	if(memo[pos]!=-1) return memo[pos];
	int m = 0;
	for(int i = min(10,int(S.size())-pos); i >= 1; i--) {//find the maximum of taking all possible primitives from the from and then calling the rest of the recursion
		if(prims.count(S.substr(pos,i)))
			m = max(m,i+count(pos+i));
	}
	return memo[pos] = m;
}

int main() {
	ios::sync_with_stdio(0);
	ifstream in("prefix.in");
	ofstream out("prefix.out");

	//take input
	string t;
	while(in>>t&&t!=".") prims.insert(t); 
	S.resize(250000);
	in >> t; S = t;
	while(in>>t) S+=t;
 	//print output
 	fill(memo,memo+S.size(),-1);
 	for(int i = S.size()-5000; i >= 1; i-=5000) { //helps limit deep recursion
 		count(i);
 	}
 	out << count(0) << '\n';
	return 0;
}
