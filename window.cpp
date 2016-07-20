/*
ID: lamorea1
LANG: C++11
PROG: window
*/
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct rect {
	int left, right, top, bottom;	
};
rect Rect(int x, int y, int X, int Y) {
	rect ret;
	ret.left = min(x,X);
	ret.right = max(x,X);
	ret.top = max(y,Y);
	ret.bottom = min(y,Y);
	return ret;
}

vector<rect> rects; //stores the dimensions of each window
vector<int> height; //stores height of each window
map<char, int> ind; //stores index associated with each id

//adds a new window to rects array
void w(string line) {
	//parse parameters
	char id = line[0];
	line = line.substr(2);
	int x = stoi(line.substr(0,line.find(",")));
	line = line.substr(line.find(",")+1);
	int y = stoi(line.substr(0,line.find(",")));
	line = line.substr(line.find(",")+1);
	int X = stoi(line.substr(0,line.find(",")));
	line = line.substr(line.find(",")+1);
	int Y = stoi(line);
	//create rect
	ind[id] = (int)rects.size();
	height.push_back((int)rects.size());
	rects.push_back(Rect(x,y,X,Y));
}
//deletes this window from the array rects
void d(string line) { int j = ind[line[0]];
	for(int i = 0; i < height.size(); i++) if(height[i] > height[j]) height[i]--;
	rects.erase(rects.begin()+j);
	height.erase(height.begin()+j);
	ind.erase(line[0]);
	for(pair<char, int> i : ind) if(ind[i.first] > j) ind[i.first]--;
}
//moves this window to the lowest height
void b(string line) {int j = ind[line[0]];
	for(int i = 0; i < height.size(); i++) if(height[i] < height[j]) height[i]++;
	height[j] = 0;
}
//moves this window to the highest height
void t(string line) {int j = ind[line[0]];
	for(int i = 0; i < height.size(); i++) if(height[i] > height[j]) height[i]--;
	height[j] = height.size()-1;
}
//prints the area visible of this window
void s(string line) {int j = ind[line[0]];
	vector<rect> curr; curr.push_back(rects[j]);
	double area = (curr[0].right - curr[0].left) * (curr[0].top - curr[0].bottom);

	//compare this rectangle with all other rectangles and see if they overlap (if so subtract that area from the total area and split this old rectangle into eight new rectangles which don't overlap anymore (area greater than or equal to 0))
	bool con = true;
	while(con) {
		con = false;
		for(int i = 0; i < rects.size()&&!con; i++) {if(height[i] <= height[j]) continue;
			//check if it overlaps with any of the curr rectangles
			int n = curr.size();
			for(int k = 0; k < n; k++) {
				int left, right, top, bottom; //stores the dimensions of the overlap rectangle
				left = max(rects[i].left,curr[k].left);
				right = min(rects[i].right,curr[k].right);
				top = min(rects[i].top,curr[k].top);
				bottom = max(rects[i].bottom,curr[k].bottom);

				if(left < right && bottom < top) { // if they overlap
					con = true;
					//split the rest of the non overlap area into 8 rectangles which do not overlap
					curr.push_back(Rect(right,top,left,curr[k].top));
					curr.push_back(Rect(right,bottom,left,curr[k].bottom));
					curr.push_back(Rect(right,top,curr[k].right,bottom));
					curr.push_back(Rect(left,top,curr[k].left,bottom));
					curr.push_back(Rect(left,top,curr[k].left,curr[k].top));
					curr.push_back(Rect(right,top,curr[k].right,curr[k].top));
					curr.push_back(Rect(right,bottom,curr[k].right,curr[k].bottom));
					curr.push_back(Rect(left,bottom,curr[k].left,curr[k].bottom));
					curr.erase(curr.begin()+k); n--; k--; //delete the old rect
				}
			}
		}
	}

	//sum total area of whats left
	double total = 0;
	for(int i = 0; i < curr.size(); i++) total += (curr[i].right - curr[i].left) * (curr[i].top - curr[i].bottom);
	printf("%.3f\n",total/area*100);
}

int main() {
	freopen("window.in","r",stdin);
	freopen("window.out","w",stdout);

	char temp[1000];
	while(scanf("%s",temp)!=EOF) {
		string line = temp;
		switch(line[0])  {
			case 'w':
				w(line.substr(line.find("(")+1,line.find(")")-line.find("(")-1));
				break;
			case 'd':
				d(line.substr(line.find("(")+1,line.find(")")-line.find("(")-1));
				break;
			case 's':
				s(line.substr(line.find("(")+1,line.find(")")-line.find("(")-1));
				break;
			case 'b':
				b(line.substr(line.find("(")+1,line.find(")")-line.find("(")-1));
				break;
			case 't':
				t(line.substr(line.find("(")+1,line.find(")")-line.find("(")-1));
				break;
		}
	}

	return 0;
}
