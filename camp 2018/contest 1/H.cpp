#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

template <typename T>
struct SegmentTree{
	SegmentTree *left, *right;
	int start, end, half;
	T value, lazy;

	SegmentTree(int start, int end){
		this->start = start;
		this->end = end;
		this->half = start + ((end - start) >> 1);
		this->value = this->lazy = 0;
		if(start == end){
			this->left = this->right = NULL;
		}else{
			this->left = new SegmentTree(start, this->half);
			this->right = new SegmentTree(this->half + 1, end);
		}
	}

	void propagate(T dif){
		this->value += dif;
		if(this->start != this->end){
			this->left->lazy += dif;
			this->right->lazy += dif;
		}
	}

	void add(T dif, int start, int end){
		if(this->lazy != 0){
			this->propagate(this->lazy);
			this->lazy = 0;
		}
		if(start > end)
			return;
		if(start == this->start && end == this->end)
			this->propagate(dif);
		else{
			this->left->add(dif, start, min(end, this->half));
			this->right->add(dif, max(start, this->half + 1), end);
			this->value = max(this->left->value, this->right->value);
		}
	}

	T query(int start, int end){
		if(this->lazy != 0){
			this->propagate(this->lazy);
			this->lazy = 0;
		}
		if(start > end)
			return 0;
		if(start == this->start && end == this->end)
			return this->value;
		return max(this->left->query(start, min(end, this->half)), this->right->query(max(start, this->half + 1), end));
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q, l, r;
	char t;
	int value;
	cin >> n;
	SegmentTree<lli> *ST = new SegmentTree<lli>(1, n);
	for(int i = 1; i <= n; i++){
		cin >> value;
		ST->add(value, i, i);
	}
	cin >> q;
	for(int i = 1; i <= q; i++){
		cin >> t;
		cin >> l >> r;
		if(t == 'm'){
			cout << ST->query(l, r) << " ";
		}else{
			cin >> value;
			ST->add(value, l, r);
		}
	}
	return 0;
}