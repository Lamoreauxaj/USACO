/*
ID: lamorea1
LANG: C++
PROG: milk3
*/
#include <cstdio>
#include <set>
using namespace std;

struct State {
	int st[3];
	State(int a, int b, int c) {
		st[0] = a; st[1] = b; st[2] = c;
	}
	State clone() {
		return State(st[0],st[1],st[2]);
	}
};

bool found[25][25][25]; //stores whether each state was reached
int caps[3]; //stores capacity of each bucket

//returns a new state with milk moved from bucket origin to bucket dst
State move(int origin, int dst, State st) {
	st = st.clone();
	int open = caps[dst]-st.st[dst];
	if(st.st[origin] >= open) {
		st.st[origin]-=open;
		st.st[dst] = caps[dst];
	}else if(st.st[origin] < open) {
		st.st[dst] += st.st[origin];
		st.st[origin] = 0;
	}return st;
}

//recursively trys all moves until it runs into past states
void solve(State st) {
	if(found[st.st[0]][st.st[1]][st.st[2]]) return;
	found[st.st[0]][st.st[1]][st.st[2]] = true;
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) { if(i==j) continue; solve(move(i,j,st)); }
}

int main() {
	freopen("milk3.in","r",stdin);
	freopen("milk3.out","w",stdout);

	//take input
	scanf("%d %d %d",&caps[0],&caps[1],&caps[2]);


	solve(State(0,0,caps[2]));


	//check which states were reached and print out the amount of milk in bucket 2
	bool first = true;
	for(int b = caps[1]; b >= 0; b--) {
		if(found[0][b][caps[2]-b]) {
			printf("%s%d",first?"":" ",caps[2]-b);
			first = false;
		}
	}printf("\n");


	return 0;
}
