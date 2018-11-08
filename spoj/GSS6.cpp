#include <bits/stdc++.h>
using namespace std;
using lli = int;

struct Treap{
	Treap *left, *right;
	lli value;
	int key, size;

	lli prefMax, suffMax, maxSum, sum;

	Treap(lli value = 0): value(value), size(1), left(NULL), right(NULL), key(rand()){
		prefMax = suffMax = maxSum = sum = value;
	}
};

inline int nodeSize(Treap* T){return T ? T->size: 0;}

void combine(Treap* &a, Treap* &b, Treap* &c){
	lli sum = a->sum + b->sum;
	lli prefMax = max(a->prefMax, a->sum + b->prefMax);
	lli suffMax = max(b->suffMax, b->sum + a->suffMax);
	lli maxSum = max({prefMax, suffMax, a->maxSum, b->maxSum, a->suffMax + b->prefMax});
	c->sum = sum;
	c->prefMax = prefMax;
	c->suffMax = suffMax;
	c->maxSum = maxSum;
}

inline void update(Treap* &T){
	if(T){
		T->size = 1 + nodeSize(T->left) + nodeSize(T->right);
		T->prefMax = T->suffMax = T->maxSum = T->sum = T->value;
		if(T->left) combine(T->left, T, T);
		if(T->right) combine(T, T->right, T);
	}
}

void split2(Treap* T, int i, Treap* &T1, Treap* &T2){
	if(!T)
		return void(T1 = T2 = NULL);
	int curr = nodeSize(T->left);
	if(i <= curr)
		split2(T->left, i, T1, T->left), T2 = T;
	else
		split2(T->right, i - curr - 1, T->right, T2), T1 = T;
	update(T);
}

void merge2(Treap* &T, Treap* T1, Treap* T2){
	if(!T1) T = T2;
	else if(!T2) T = T1;
	else if(T1->key > T2->key)
		merge2(T1->right, T1->right, T2), T = T1;
	else
		merge2(T2->left, T1, T2->left), T = T2;
	update(T);
}

void insert_at(Treap* &T, lli x, int i){
	if(i > nodeSize(T)) return;
	Treap *T1 = NULL, *T2 = NULL;
	split2(T, i, T1, T2);
	merge2(T, T1, new Treap(x));
	merge2(T, T, T2);
}

void erase_at(Treap* &T, int i){
	if(i >= nodeSize(T)) return;
	Treap *T1 = NULL, *T2 = NULL, *T3 = NULL;
	split2(T, i, T1, T2);
	split2(T2, 1, T2, T3);
	merge2(T, T1, T3);
}

void update_at(Treap* T, lli x, int i){
	assert(0 <= i && i < nodeSize(T));
	int curr = nodeSize(T->left);
	if(i == curr)
		T->value = x;
	else if(i < curr)
		update_at(T->left, x, i);
	else
		update_at(T->right, x, i - curr - 1);
	update(T);
}

lli query(Treap* &T, int l, int r){
	Treap *T1 = NULL, *T2 = NULL, *T3 = NULL;
	split2(T, l, T1, T2);
	split2(T2, r - l + 1, T2, T3);
	lli ans = T2->maxSum;
	merge2(T, T1, T2);
	merge2(T, T, T3);
	return ans;
}

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, x, y;
	char t;
	lli ai;
	cin >> n;
	Treap* T = NULL;
	for(int i = 0; i < n; ++i){
		cin >> ai;
		insert_at(T, ai, i);
	}
	cin >> q;
	while(q--){
		cin >> t;
		if(t == 'I'){
			cin >> x >> y;
			insert_at(T, y, x - 1);
		}else if(t == 'D'){
			cin >> x;
			erase_at(T, x - 1);
		}else if(t == 'R'){
			cin >> x >> y;
			update_at(T, y, x - 1);
		}else{
			cin >> x >> y;
			cout << query(T, x - 1, y - 1) << "\n";
		}
	}
	return 0;
}