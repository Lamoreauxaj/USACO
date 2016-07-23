/*
ID: lamorea1
LANG: C++11
PROG: money
*/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
ifstream in("money.in");
ofstream out("money.out");

int val[30];
int N, V;
long long memo[11000][30];

//coin change problem, pretty simple
long long change(int n, int pos) {
	if(pos==V) { //if out of coins
		if(n==0) return 1; //1 way to have 0 money with 0 coins
		else return 0; //0 ways to have not 0 money with 0 coins
	}
	if(memo[n][pos]!=-1) return memo[n][pos];

	long long sum = 0;
	sum+=change(n,pos+1); //try not taking this coin and moving on
	if(n>=val[pos]) sum+=change(n-val[pos],pos); //try taking this coin if we can
	return memo[n][pos] = sum; //return the num possible ways
}

int main() {

	//take input
	in >> V >> N;
	for(int i = 0; i < V; i++) in >> val[i];

	//init memo
	for(int i = 0; i <= N; i++) {
		for(int j = 0; j < V; j++) memo[i][j] = -1;
	}

	//call method
	out << change(N,0) << '\n';

	return 0;
}
