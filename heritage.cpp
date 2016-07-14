/*
ID: lamorea1
LANG: C++11
PROG: heritage
*/
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

struct Node {
	struct Node* left; struct Node* right;
	Node(string preorder, string inorder) { //creates a tree from the postorder and inorders
		left = right = NULL;
		val = preorder[0];
		if(preorder.size()==1) return;
		int t = inorder.find(val);
		string li = inorder.substr(0,t);
		string lp = preorder.substr(1,t);
		if(lp.size()>0) left = new Node(lp,li);
		string ri = inorder.substr(t+1);
		string rp = preorder.substr(t+1);
		if(rp.size()>0) right = new Node(rp,ri);
	}
	~Node() { //deletes tree because we are using pointers
		delete left;
		delete right;
	}
	char val;
};

//returns post order of node t
string post(Node* t) {
	if(t==NULL) return "";
	return post(t->left)+post(t->right)+char(t->val);
}

int main() {
	freopen("heritage.in","r",stdin);
	freopen("heritage.out","w",stdout);

	//input
	string preorder, inorder;
	cin >> inorder >> preorder;
	Node t(preorder,inorder);

	//output
	printf("%s\n",post(&t).c_str());

	return 0;
}
