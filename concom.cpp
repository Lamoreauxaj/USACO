/*
ID: lamorea1
LANG: C++11
PROG: concom
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("concom.in");
ofstream out("concom.out");

int control[110][110];

bool visited[110];
int owns[110];

//recurse through to find all companies that n owns
void recurse(int n) {
	visited[n] = true;
	for(int k = 1; k <= 100; k++) {
		owns[k]+=control[n][k];
		if(owns[k]>50&&!visited[k]&&k!=n) {
			recurse(k);
		}
	}
}

int main() {

	//init control to 0
	for(int i = 0; i < 110; i++)
		for(int j = 0; j < 110; j++) control[i][j] = 0;

	//take input
	int n;
	in >> n; int i, j, p;
	while(n--) {
		in >> i >> j >> p;
		control[i][j]+=p;
	}

	//print output
	//recurse for each company to see all the other companies they own
	for(int i = 1; i <= 100; i++) {
		for(int j = 1; j <= 100; j++) owns[j] = visited[j] = 0;
		recurse(i);
		for(int j = 1; j <= 100; j++) {if(i==j) continue;
			if(owns[j]>50) out << i << " " << j << '\n';
		}
	}

	return 0;
}
