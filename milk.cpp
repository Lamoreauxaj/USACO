/*
ID: lamorea1
LANG: C++
PROG: milk
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int need, num_farmers;

struct Farmer {
	int price, amt;
	bool operator <(Farmer other) const { return price < other.price; }
};
Farmer farmers[5050];

int main() {
	freopen("milk.in","r",stdin);
	freopen("milk.out","w",stdout);

	scanf("%d %d",&need,&num_farmers);
	for(int i = 0; i < num_farmers; i++) scanf("%d %d",&farmers[i].price,&farmers[i].amt);
	sort(farmers,farmers+num_farmers);

	int total = 0;
	int pos = 0;
	while(need>0) {
		if(farmers[pos].amt<=need) {
			need-=farmers[pos].amt;
			total+=farmers[pos].amt*farmers[pos].price;
			pos++;
		}else {
			total+=need*farmers[pos].price;
			need = 0;
			pos++;
		}
	}
	printf("%d\n",total);

	return 0;
}
