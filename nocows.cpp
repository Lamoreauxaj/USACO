/*
ID: lamorea1
LANG: C++11
PROG: nocows
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("nocows.in");
ofstream out("nocows.out");

int N, K;

pair<int,int> memo[220][220];

//returns num ways using N nodes and K height
//pair<num ways that already reach K,num ways less than K (other side must reach K)> discard those that go past K 
pair<int,int> f(int n, int lev) {
	if(lev>K) return pair<int,int>(0,0); //always 0 no need to find number of ways we don't care
	if(memo[n][lev]!=pair<int,int>(-1,-1)) return memo[n][lev];
	if(n==1) { 
		if(lev==K) return memo[n][lev] = pair<int,int>(1,0); //lev==K
		else return memo[n][lev] = pair<int,int>(0,1); //lev<K
	}
	int sumk = 0, sumltk = 0; pair<int,int> left; pair<int,int> right;
	for(int i = 1; i < n-1; i++) {
		left = f(i,lev+1);
		right = f(n-i-1, lev+1);
		sumk+=left.first*right.first+left.first*right.second+right.first*left.second; //all have atleast a k depth
		sumk%=9901;
		sumltk+=left.second*right.second; //still valid number of ways with N nodes just without k height
		sumltk%=9901;
	}
	return memo[n][lev] = pair<int,int>(sumk,sumltk); 
}

int main() {

	in >> N >> K;

	for(int i = 0; i <= N; i++)
		for(int j = 0; j <= N; j++) memo[i][j] = pair<int,int>(-1,-1);
	out << f(N,1).first << '\n';

	return 0;
}
