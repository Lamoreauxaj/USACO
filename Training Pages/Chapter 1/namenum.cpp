/*
ID: lamorea1
LANG: C++
PROG: namenum
*/
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

char serial[15];
char word[50];
map<char,char> val;

void init() {
	val['A'] = '2'; val['B'] = '2'; val['C'] = '2';
	val['D'] = '3'; val['E'] = '3'; val['F'] = '3';
	val['G'] = '4'; val['H'] = '4'; val['I'] = '4';
	val['J'] = '5'; val['K'] = '5'; val['L'] = '5';
	val['M'] = '6'; val['N'] = '6'; val['O'] = '6';
	val['P'] = '7'; val['R'] = '7'; val['S'] = '7';
	val['T'] = '8'; val['U'] = '8'; val['V'] = '8';
	val['W'] = '9'; val['X'] = '9'; val['Y'] = '9';
	val['Q'] = '!'; val['Z'] = '!';
}

char temp[50];

char* change() {
	for(int i = 0; i < strlen(word); i++) temp[i] = val[word[i]];
	temp[strlen(word)] = '\0';
	return temp;
}

int main() {
	freopen("namenum.in","r",stdin);
	freopen("namenum.out","w",stdout);

	scanf("%s",serial);
	init();

	freopen("dict.txt", "r", stdin);

	bool found = false;
	while(scanf("%s",word)!=EOF) {
		if(strcmp(serial,change())==0) {
			printf("%s\n",word); found = true; }
	}

	if(!found) printf("NONE\n");

	return 0;
}
