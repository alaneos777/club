#include <bits/stdc++.h>
using namespace std;

struct Treap{
	Treap *left, *right;
	int value;
	int key, size;

	Treap(int value = 0): value(value), key(rand()), size(1), left(NULL), right(NULL){}

	inline void update(){
		size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
	}
};

inline int nodeSize(Treap* &pos){
	return pos ? pos->size: 0;
}

void merge(Treap* &T, Treap* T1, Treap* T2){
	if(!T1) T = T2;
	else if(!T2) T = T1;
	else if(T1->key > T2->key)
		merge(T1->right, T1->right, T2), T = T1;
	else
		merge(T2->left, T1, T2->left), T = T2;
	if(T) T->update();
}

void split(Treap* T, int x, Treap* &T1, Treap* &T2){
	if(!T)
		return void(T1 = T2 = NULL);
	if(x < T->value)
		split(T->left, x, T1, T->left), T2 = T;
	else
		split(T->right, x, T->right, T2), T1 = T;
	if(T) T->update();
}

Treap* search(Treap* T, int x){
	while(T){
		if(x == T->value) break;
		T = (x < T->value ? T->left : T->right);
	}
	return T;
}

void insert(Treap* &T, Treap* x){
	if(!T) T = x;
	else if(x->key > T->key)
		split(T, x->value, x->left, x->right), T = x;
	else
		insert(x->value < T->value ? T->left : T->right, x);
	if(T) T->update();
}

void insert(Treap* &T, int x){
	insert(T, new Treap(x));
}

void erase(Treap* &T, int x){
	if(!T) return;
	if(T->value == x)
		merge(T, T->left, T->right);
	else
		erase(x < T->value ? T->left : T->right, x);
	if(T) T->update();
}

int lessThan(Treap* T, int x){
	int ans = 0;
	while(T){
		if(x > T->value){
			ans += nodeSize(T->left) + 1;
			T = T->right;
		}else{
			T = T->left;
		}
	}
	return ans;
}

int kth(Treap* T, int i){
	while(i != nodeSize(T->left)){
		if(i < nodeSize(T->left)){
			T = T->left;
		}else{
			i -= nodeSize(T->left) + 1;
			T = T->right;
		}
	}
	return T->value;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t, n;
	Treap* T = NULL;
	while(cin >> t && t != -1){
		cin >> n;
		if(t == 1) insert(T, n);
		else if(t == 2) erase(T, n);
		else if(t == 3){
			if(search(T, n)) cout << 1+lessThan(T, n) << "\n";
			else cout << "-1\n";
		}else{
			if(1 <= n && n <= nodeSize(T)) cout << kth(T, n-1) << "\n";
			else cout << "-1\n";
		}
	}
	return 0;
}