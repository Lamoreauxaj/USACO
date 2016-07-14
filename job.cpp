/*
ID: lamorea1
LANG: C++11
PROG: job
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int N, m1, m2;
vector<int> m1fin;
vector<int> m2fin;
int m1time[30];
int m2time[30];
int m1pos[30];
int m2pos[30];

int main() {
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);

	//input
	scanf("%d",&N);
	scanf("%d %d",&m1,&m2);
	for(int i = 0; i < m1; i++) {
		scanf("%d",&m1time[i]);
		m1pos[i] = 0;
	}for(int i = 0; i < m2; i++) {
		scanf("%d",&m2time[i]);
		m2pos[i] = 0;
	}

	//calculate time for each item to finish in A machines
	for(int j = 0; j < N; j++) {
		int mini = 1000000000; int best = -1;
		for(int i = 0; i < m1; i++) {
			if(m1pos[i]+m1time[i] < mini) {
				mini = m1pos[i] + m1time[i];
				best = i;
			}
		}
		m1pos[best] = mini;
		m1fin.push_back(mini);
	}

	//calculate time for each item to finish in B machines
	for(int j = 0; j < N; j++) {
		int mini = 1000000000; int best = -1;
		for(int i = 0; i < m2; i++) {
			if(m2pos[i]+m2time[i] < mini) {
				mini = m2pos[i] + m2time[i];
				best = i;
			}
		}
		m2pos[best] = mini;
		m2fin.push_back(mini);
	}

	sort(m1fin.begin(),m1fin.end());
	sort(m2fin.begin(),m2fin.end());
	int maxi = 0;
	for(int i = 0; i < N; i++) {
		maxi = max(maxi,m1fin[i]+m2fin[N-i-1]);
	}

	printf("%d %d\n",m1fin[m1fin.size()-1],maxi);

	return 0;
}
