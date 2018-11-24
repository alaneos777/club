#include <bits/stdc++.h>
using namespace std;

struct Treap{
	Treap *left, *right;
	bool value;
	int key, size;

	int sum;
	short int action;

	Treap(bool value = 0): value(value), key(rand()), size(1), left(NULL), right(NULL), sum(value), action(-1){}
};

inline int nodeSize(Treap* T){return T ? T->size: 0;}

inline int nodeSum(Treap* T){return T ? T->sum : 0;}

inline short int newAction(int oldAction){
	if(oldAction == -1) return 2;
	if(oldAction == 0) return 1;
	if(oldAction == 1) return 0;
	if(oldAction == 2) return -1;
}

inline void push(Treap* T){
	if(!T) return;
	if(T->action == 0 || T->action == 1){
		T->value = T->action;
		T->sum = T->action ? T->size : 0;
		if(T->left) T->left->action = T->action;
		if(T->right) T->right->action = T->action;
	}else if(T->action == 2){
		T->value ^= 1;
		T->sum = T->size - T->sum;
		if(T->left) T->left->action = newAction(T->left->action);
		if(T->right) T->right->action = newAction(T->right->action);
	}
	T->action = -1;
}

inline void update(Treap* T){
	if(T){
		T->size = 1 + nodeSize(T->left) + nodeSize(T->right);
		T->sum = T->value;
		push(T->left), push(T->right);
		T->sum = T->value + nodeSum(T->left) + nodeSum(T->right);
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
	update(T);
}

void merge2(Treap* &T, Treap* T1, Treap* T2){
	push(T1), push(T2);
	if(!T1) T = T2;
	else if(!T2) T = T1;
	else if(T1->key > T2->key)
		merge2(T1->right, T1->right, T2), T = T1;
	else
		merge2(T2->left, T1, T2->left), T = T2;
	update(T);
}

void insert_at(Treap* &T, bool x, int i){
	Treap *T1 = NULL, *T2 = NULL;
	split2(T, i, T1, T2);
	merge2(T, T1, new Treap(x));
	merge2(T, T, T2);
}

void update_range(Treap* &T, int action, int l, int r){
	Treap *T1 = NULL, *T2 = NULL, *T3 = NULL;
	split2(T, l, T1, T2);
	split2(T2, r - l + 1, T2, T3);
	T2->action = action;
	merge2(T, T1, T2);
	merge2(T, T, T3);
}

int sum_query(Treap* &T, int l, int r){
	Treap *T1 = NULL, *T2 = NULL, *T3 = NULL;
	split2(T, l, T1, T2);
	split2(T2, r - l + 1, T2, T3);
	int ans = nodeSum(T2);
	merge2(T, T1, T2);
	merge2(T, T, T3);
	return ans;
}

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int cases;
	cin >> cases;
	for(int caso = 1; caso <= cases; ++caso){
		int m, n = 0, t, q, l, r;
		char c;
		cin >> m;
		string str;
		stringstream ss;
		while(m--){
			cin >> t >> str;
			n += t * str.size();
			while(t--){
				ss << str;
			}
		}
		str = ss.str();
		Treap* T = NULL;
		for(int i = 0; i < n; ++i){
			insert_at(T, str[i]-'0', i);
		}
		cin >> q;
		cout << "Case " << caso << ":\n";
		int query = 1;
		while(q--){
			cin >> c >> l >> r;
			if(c == 'F'){
				update_range(T, 1, l, r); //set
			}else if(c == 'E'){
				update_range(T, 0, l, r); //clear
			}else if(c == 'I'){
				update_range(T, 2, l, r); //flip
			}else{
				cout << "Q" << query++ << ": " << sum_query(T, l, r) << "\n";
			}
		}
	}
	return 0;
}