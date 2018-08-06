#include <bits/stdc++.h>
using namespace std;

struct node{
	int prefMax, suffMax, maxSum, sum;
};

node combine(const node & a, const node & b){
	node c;
	c.sum = a.sum + b.sum;
	c.prefMax = max(a.prefMax, a.sum + b.prefMax);
	c.suffMax = max(b.suffMax, b.sum + a.suffMax);
	c.maxSum = max(c.prefMax, c.suffMax);
	c.maxSum = max(c.maxSum, a.maxSum);
	c.maxSum = max(c.maxSum, b.maxSum);
	c.maxSum = max(c.maxSum, a.suffMax + b.prefMax);
	return c;
}

template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;

	SegmentTree(int N){
		this->N = N;
		ST.resize(N << 1);
	}

	void build(){
		for(int i = N - 1; i > 0; --i)
			ST[i] = combine(ST[i << 1], ST[i << 1 | 1]);
	}

	T query(int l, int r){
		T left, right;
		bool le = false, ri = false;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1) {
			if(l & 1){
				if(le) left = combine(left, ST[l++]);
				else left = ST[l++], le = true;
			}
			if(!(r & 1)){
				if(ri) right = combine(ST[r--], right);
				else right = ST[r--], ri = true;
			}
		}
		if(le && ri) return combine(left, right);
		else if(le) return left;
		else return right;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, q, x, l, r;
	cin >> n;
	SegmentTree<node> *st = new SegmentTree<node>(n);
	for(int i = 0; i < n; ++i){
		cin >> x;
		st->ST[n + i] = {x, x, x, x};
	}
	st->build();
	cin >> q;
	while(q--){
		cin >> l >> r;
		cout << st->query(l - 1, r - 1).maxSum << "\n";
	}
	return 0;
}