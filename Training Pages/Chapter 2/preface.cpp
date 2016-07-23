/*
ID: lamorea1
LANG: C++
PROG: preface
*/
#include <cstdio>
using namespace std;

int N;

int main() {
	freopen("preface.in","r",stdin);
	freopen("preface.out","w",stdout);

	scanf("%d",&N);

	int total[] = {0,0,0,0,0,0,0};

	//count totals of each character
	//does so by treating each power of ten place seperately
	//this means we only have to code 4 sections of code and it works on all 3,500 numbers
	int thousands, hundreds, tens, ones;
	for(int i = 1; i <= N; i++) {
		ones = i%10;
		tens = i%100/10;
		hundreds = i%1000/100;
		thousands = i/1000;
		switch(ones) {
			case 1:
			total[0]+=1;
			break;
			case 2:
			total[0]+=2;
			break;
			case 3:
			total[0]+=3;
			break;
			case 4:
			total[0]+=1; total[1]+=1;
			break;
			case 5:
			total[1]+=1;
			break;
			case 6:
			total[1]+=1; total[0]+=1;
			break;
			case 7:
			total[1]+=1; total[0]+=2;
			break;
			case 8:
			total[1]+=1; total[0]+=3;
			break;
			case 9:
			total[0]+=1; total[2]+=1;
			break;
		}
		switch(tens) {
			case 1:
			total[2]+=1;
			break;
			case 2:
			total[2]+=2;
			break;
			case 3:
			total[2]+=3;
			break;
			case 4:
			total[2]+=1; total[3]+=1;
			break;
			case 5:
			total[3]+=1;
			break;
			case 6:
			total[3]+=1; total[2]+=1;
			break;
			case 7:
			total[3]+=1; total[2]+=2;
			break;
			case 8:
			total[3]+=1; total[2]+=3;
			break;
			case 9:
			total[2]+=1; total[4]+=1;
			break;
		}
		switch(hundreds) {
			case 1:
			total[4]+=1;
			break;
			case 2:
			total[4]+=2;
			break;
			case 3:
			total[4]+=3;
			break;
			case 4:
			total[4]+=1; total[5]+=1;
			break;
			case 5:
			total[5]+=1;
			break;
			case 6:
			total[5]+=1; total[4]+=1;
			break;
			case 7:
			total[5]+=1; total[4]+=2;
			break;
			case 8:
			total[5]+=1; total[4]+=3;
			break;
			case 9:
			total[4]+=1; total[6]+=1;
			break;
		}
		switch(thousands) {
			case 1:
			total[6]+=1;
			break;
			case 2:
			total[6]+=2;
			break;
			case 3:
			total[6]+=3;
			break;
		}
	}

	//print output
	for(int i = 0; i < 7; i++) {
		if(total[i]==0) break;
		switch(i) {
			case 0:
			printf("I %d\n",total[i]);
			break;
			case 1:
			printf("V %d\n",total[i]);
			break;
			case 2:
			printf("X %d\n",total[i]);
			break;
			case 3:
			printf("L %d\n",total[i]);
			break;
			case 4:
			printf("C %d\n",total[i]);
			break;
			case 5:
			printf("D %d\n",total[i]);
			break;
			case 6:
			printf("M %d\n",total[i]);
			break;
		}
	}

	return 0;
}
