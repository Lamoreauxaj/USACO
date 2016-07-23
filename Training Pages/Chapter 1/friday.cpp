/*
ID: lamorea1
LANG: C++
PROG: friday
*/
#include <cstdio>
using namespace std;

int N;
int freq[7];

int startday(int year) {
	int numleaps = (year-1-1900)/4;
	numleaps -= (year-1-1900)/100;
	numleaps += (year-1-1600)/400;
	return (2+(year-1900)+numleaps)%7;
}

bool isleap(int year) {
	if(year%400==0) return true;
	if(year%100==0) return false;
	return year%4==0;
}

int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
int day(int month, int day) {
	int sum = day;
	for(int i = 1; i < month; i++)
		sum+=months[i-1];
	return sum;
}

void compute(int year) {
	int start = startday(year)-1;
	int shift = isleap(year)?1:0;
	for(int mon = 1; mon <= 12; mon++) {
		if(mon>2) freq[(day(mon,13)+start+shift)%7]++;
		else freq[(day(mon,13)+start)%7]++;
	}
}

int main() {
	freopen("friday.in","r",stdin);
	freopen("friday.out","w",stdout);

	scanf("%d",&N);
	for(int i = 0; i < N; i++)
		compute(1900+i);

	printf("%d",freq[0]); for(int i = 1; i < 7; i++) printf(" %d",freq[i]); printf("\n");

	return 0;
}
