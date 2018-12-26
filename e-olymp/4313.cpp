#include <bits/stdc++.h>
using namespace std;

const int M = 2e5 + 10;

struct node{
	node* next;
	int val;
	node(int val): val(val) {}
};

node* push(node* p, int val){
	node* t = new node(val);
	t->next = p;
	return t;
}

node* pop(node* &p){
	assert(p);
	cout << p->val << "\n";
	return p->next;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<node*> versions(M + 1);
	int q, t, m;
	cin >> q;
	for(int i = 1; i <= q; ++i){
		cin >> t >> m;
		if(m == 0){
			versions[i] = pop(versions[t]);
		}else{
			versions[i] = push(versions[t], m);
		}
	}
	return 0;
}