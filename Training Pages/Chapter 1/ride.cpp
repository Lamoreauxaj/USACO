/*
ID: lamorea1
LANG: C++
PROG: ride
*/
#include <cstdio>
#include <cstring>
using namespace std;

char word1[10];
char word2[10];

int main() {	
	freopen("ride.in","r",stdin);
	freopen("ride.out","w",stdout);

	scanf("%s",word1);
	scanf("%s",word2);

	int val1 = 1;
	int val2 = 1;
	for(int i = 0; i < strlen(word1); i++)
		val1*=word1[i]-64;
	for(int i = 0; i < strlen(word2); i++)
		val2*=word2[i]-64;

	if(val1%47==val2%47) printf("GO\n");
	else printf("STAY\n");

	return 0;
}
