#include <bits/stdc++.h>
using namespace std;

struct Treap{
	Treap *left, *right;
	int value;
	int size;

	bool rev;

	Treap(int value = 0): value(value), size(1), left(NULL), right(NULL), rev(false){}

	inline void update(){
		size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
	}
};

inline int nodeSize(Treap* &pos){
	return pos ? pos->size: 0;
}

void push(Treap* T){
	if(T && T->rev){
		T->rev = false;
		swap(T->left, T->right);
		if(T->left) T->left->rev ^= true;
		if(T->right) T->right->rev ^= true;
	}
}

void split2(Treap* T, int i, Treap* &T1, Treap* &T2){
	if(!T)
		return void(T1 = T2 = NULL);
	push(T);
	int curr = nodeSize(T->left);
	if(i <= curr)
		split2(T->left, i, T1, T->left), T2 = T;
	else
		split2(T->right, i - curr - 1, T->right, T2), T1 = T;
	if(T) T->update();
}

inline int random(){
	return (rand() << 15) + rand();
}

void merge2(Treap* &T, Treap* T1, Treap* T2){
	push(T1), push(T2);
	if(!T1) T = T2;
	else if(!T2) T = T1;
	else if(random() % (nodeSize(T1) + nodeSize(T2)) < nodeSize(T1))
		merge2(T1->right, T1->right, T2), T = T1;
	else
		merge2(T2->left, T1, T2->left), T = T2;
	if(T) T->update();
}

void insert_at(Treap* &T, int x, int i){
	if(i > nodeSize(T)) return;
	Treap *T1 = NULL, *T2 = NULL;
	split2(T, i, T1, T2);
	merge2(T, T1, new Treap(x));
	merge2(T, T, T2);
}

int nth(Treap* T, int i){
	push(T);
	assert(0 <= i && i < nodeSize(T));
	int curr = nodeSize(T->left);
	if(i == curr)
		return T->value;
	else if(i < curr)
		return nth(T->left, i);
	else
		return nth(T->right, i - curr - 1);
}

void reverse_update(Treap* &T, int l, int r){
	Treap *T1 = NULL, *T2 = NULL, *T3 = NULL;
	split2(T, l, T1, T2);
	split2(T2, r - l + 1, T2, T3);
	T2->rev ^= true;
	merge2(T, T1, T2);
	merge2(T, T, T3);
}

void rotate_update(Treap* &T, int k, int l, int r){
	Treap *T1 = NULL, *T2 = NULL, *T3 = NULL, *T4 = NULL;
	split2(T, l, T1, T2);
	split2(T2, r - l + 1, T2, T3);
	k %= nodeSize(T2);
	split2(T2, nodeSize(T2) - k, T2, T4);
	merge2(T, T1, T4);
	merge2(T, T, T2);
	merge2(T, T, T3);
}

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, m, ai, t, l, r, bi;
	cin >> n >> q >> m;
	Treap* T = NULL;
	for(int i = 0; i < n; ++i){
		cin >> ai;
		insert_at(T, ai, i);
	}
	while(q--){
		cin >> t >> l >> r;
		--l, --r;
		if(t == 1) rotate_update(T, 1, l, r);
		else reverse_update(T, l, r);
	}
	while(m--){
		cin >> bi;
		--bi;
		cout << nth(T, bi) << " ";
	}
	cout << "\n";
	return 0;
}