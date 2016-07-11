/*
ID: lamorea1
LANG: C++11
PROG: ttwo
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream in("ttwo.in");
ofstream out("ttwo.out");

string map[10];

int fr, fc; int fdir = 0; // 0 is north 1 is east 2 is south 3 is west 
int cr, cc; int cdir = 0;

bool inbounds(int r, int c) {
	return r>=0&&c>=0&&r<10&&c<10;
}

//moves the farmer through the grid based on the rules specified
void updatefarmer() {
	if(fdir==0) {
		if(!inbounds(fr-1,fc)||map[fr-1][fc]=='*') fdir = (fdir+1)%4;
		else fr-=1;
	}else if(fdir==1) {
		if(!inbounds(fr,fc+1)||map[fr][fc+1]=='*') fdir = (fdir+1)%4;
		else fc+=1;
	}else if(fdir==2) {
		if(!inbounds(fr+1,fc)||map[fr+1][fc]=='*') fdir = (fdir+1)%4;
		else fr+=1;
	}else if(fdir==3) {
		if(!inbounds(fr,fc-1)||map[fr][fc-1]=='*') fdir = (fdir+1)%4;
		else fc-=1;
	}
}

//moves the cow through the grid based on the rules specified
void updatecow() {
	if(cdir==0) {
		if(!inbounds(cr-1,cc)||map[cr-1][cc]=='*') cdir = (cdir+1)%4;
		else cr-=1;
	}else if(cdir==1) {
		if(!inbounds(cr,cc+1)||map[cr][cc+1]=='*') cdir = (cdir+1)%4;
		else cc+=1;
	}else if(cdir==2) {
		if(!inbounds(cr+1,cc)||map[cr+1][cc]=='*') cdir = (cdir+1)%4;
		else cr+=1;
	}else if(cdir==3) {
		if(!inbounds(cr,cc-1)||map[cr][cc-1]=='*') cdir = (cdir+1)%4;
		else cc-=1;
	}
}

int main() {

	//take input
	for(int i = 0; i < 10; i++) in >> map[i];

	//find start spots
	for(int r = 0; r < 10; r++)
		for(int c = 0; c < 10; c++)
			if(map[r][c]=='F') {
				fr = r;
				fc = c;
			}else if(map[r][c]=='C') {
				cr = r;
				cc = c;
			}

	//update farmer and cow
	int count = 0;
	while(fr!=cr||fc!=cc) {
		updatefarmer();
		updatecow();
		count++;
		if(count>=1000) break;
	}
	if(count<1000)
		out << count << '\n';
	else out << 0 << '\n';

	return 0;
}
