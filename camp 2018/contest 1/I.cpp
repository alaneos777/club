#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli inf = INT_MAX;

template <typename T>
struct SegmentTree{
	SegmentTree *left, *right;
	int start, end, half;
	T gcd;

	SegmentTree(int start, int end){
		this->start = start;
		this->end = end;
		this->half = start + ((end - start) >> 1);
		if(start == end){
			this->left = this->right = NULL;
		}else{
			this->left = new SegmentTree(start, this->half);
			this->right = new SegmentTree(this->half + 1, end);
		}
	}

	void update(T value, int start, int end){
		if(start > end)
			return;
		if(start == this->start && end == this->end)
			this->gcd = value;
		else{
			this->left->update(value, start, min(end, this->half));
			this->right->update(value, max(start, this->half + 1), end);
			this->gcd = __gcd(this->left->gcd, this->right->gcd);
		}
	}

	T query(int start, int end){
		if(start > end)
			return 0;
		if(start == this->start && end == this->end)
			return this->gcd;
		return __gcd(this->left->query(start, min(end, this->half)), this->right->query(max(start, this->half + 1), end));
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q, l, r;
	lli value;
	cin >> n;
	SegmentTree<lli> *ST = new SegmentTree<lli>(1, n);
	for(int i = 1; i <= n; i++){
		cin >> value;
		ST->update(value, i, i);
	}
	cin >> q;
	for(int i = 1; i <= q; i++){
		cin >> l >> r;
		cout << ST->query(l, r) << "\n";
	}
	return 0;
}