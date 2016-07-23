/*
ID: lamorea1
LANG: C++
PROG: castle
*/
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

enum {WEST = 1, NORTH = 2, EAST = 4, SOUTH = 8};

struct Node {
	int wall;
	int comp;
	Node() {}
	Node(int n) {wall = n; comp = -1;}
	bool haswall(int n) {return (wall&n)==n;}
};

Node castle[55][55]; //stores the data for each castle (walls & comp)
int comp_size[5000]; //stores the size of a comp
int num_comp = 0; //stores total comp number
int rows, cols; //size of the castle

//returns if vertice is within the bounds
bool inbounds(int r, int c) {
	return r>=0&&c>=0&&r<rows&&c<cols;
}

//fills all adj cells from (r,c) with num_comp
void flood_fill(int r, int c) {
	if(!inbounds(r,c)||castle[r][c].comp!=-1) return;
	castle[r][c].comp = num_comp;
	comp_size[num_comp]++;
	if(!castle[r][c].haswall(NORTH))
		flood_fill(r-1,c);
	if(!castle[r][c].haswall(SOUTH))
		flood_fill(r+1,c);
	if(!castle[r][c].haswall(WEST))
		flood_fill(r,c-1);
	if(!castle[r][c].haswall(EAST))
		flood_fill(r,c+1);
}

//marks each cell with a comp number
void find_comp() {
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			if(castle[r][c].comp==-1) {
				flood_fill(r,c);
				num_comp++;
			}
		}
	}
}

int main() {
	freopen("castle.in","r",stdin);
	freopen("castle.out","w",stdout);

	//take input
	int t;
	scanf("%d %d",&cols,&rows);
	for(int r = 0; r < rows; r++)
		for(int c = 0; c < cols; c++) {
			scanf("%d",&t);
			castle[r][c] = Node(t);
		}

	//find components
	find_comp();

	//print number of rooms
	printf("%d\n",num_comp);

	//print maximum room size
	int m = 0;
	for(int i = 0; i < num_comp; i++) m = max(m,comp_size[i]);
	printf("%d\n",m);


	//find largest creatable room
	char output[25];
	for(int c = 0; c < cols; c++) {
		for(int r = rows-1; r >= 0; r--) {
			if(inbounds(r-1,c) && castle[r][c].haswall(NORTH) && castle[r][c].comp != castle[r-1][c].comp) {
				if(comp_size[castle[r][c].comp]+comp_size[castle[r-1][c].comp]>m) {
					m = comp_size[castle[r][c].comp]+comp_size[castle[r-1][c].comp];
					sprintf(output,"%d %d N",r+1,c+1);
				}
			}
			if(inbounds(r,c+1) && castle[r][c].haswall(EAST) && castle[r][c].comp != castle[r][c+1].comp) {
				if(comp_size[castle[r][c].comp]+comp_size[castle[r][c+1].comp]>m) {
					m = comp_size[castle[r][c].comp]+comp_size[castle[r][c+1].comp];
					sprintf(output,"%d %d E",r+1,c+1);
				}
			}
		}
	}

	printf("%d\n",m);

	printf("%s\n",output);

	return 0;
}
