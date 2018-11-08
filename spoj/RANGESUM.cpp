#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct Treap{
	Treap *left, *right;
	lli value;
	int size;

	lli sum;

	Treap(lli value = 0): value(value), size(1), left(NULL), right(NULL), sum(value){}
};

inline int nodeSize(Treap* T){return T ? T->size: 0;}

inline lli nodeSum(Treap* T){return T ? T->sum: 0;}

inline void update(Treap* T){
	if(T){
		T->size = 1 + nodeSize(T->left) + nodeSize(T->right);
		T->sum = T->value + nodeSum(T->left) + nodeSum(T->right);
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

inline int aleatorio(){
	return (rand() << 15) + rand();
}

void merge2(Treap* &T, Treap* T1, Treap* T2){
	if(!T1) T = T2;
	else if(!T2) T = T1;
	else if(aleatorio() % (nodeSize(T1) + nodeSize(T2)) < nodeSize(T1))
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

lli sum_query(Treap* &T, int l, int r){
	Treap *T1 = NULL, *T2 = NULL, *T3 = NULL;
	split2(T, l, T1, T2);
	split2(T2, r - l + 1, T2, T3);
	lli ans = nodeSum(T2);
	merge2(T, T1, T2);
	merge2(T, T, T3);
	return ans;
}

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, t, l, r;
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
		if(t == 1){
			cin >> l >> r;
			--l, --r;
			cout << sum_query(T, l, r) << "\n";
		}else{
			cin >> ai;
			insert_at(T, ai, 0);
		}
	}
	return 0;
}