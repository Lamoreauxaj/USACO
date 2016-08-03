#include <cstdio>
#include <vector>
using namespace std;

int main() {
	freopen("badmilk.in","r",stdin);
	freopen("badmilk.out","w",stdout);

	//input
	int n, m, d, s;
	scanf("%d %d %d %d",&n,&m,&d,&s);
	<unordered_map<int,int> drank[50];
	for(int i = 0; i < d; i++) {
		int p, m, t;
		scanf("%d %d %d",&p,&m,&t);
		if( !drank[p].count(m) ) drank[p][m] = t;
		else drank[p][m] = min(t,drank[p][m]);
	}
	vector<int> sick;
	for(int j = 0; j < m; j++) sick.push_back(0),scanf("%d",&sick.back());

	//find which milks were drank by all the sick participants
	vector<int> milks;
	for(int i = 0; i < m; i++) {

	}
	


	return 0;
}