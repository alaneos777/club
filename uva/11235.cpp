#include <bits/stdc++.h>
using namespace std;

struct node{
	int mf, mpf, msf, mpn, msn;
};

node combine(const node & a, const node & b){
	node c;
	if(a.msn == b.mpn){
		c.mf = max(max(a.mf, b.mf), a.msf + b.mpf);
		if(a.mpn == a.msn)
			c.mpf = a.msf + b.mpf;
		else
			c.mpf = a.mpf;
		if(b.mpn == b.msn)
			c.msf = a.msf + b.mpf;
		else
			c.msf = b.msf;
	}else{
		c.mf = max(a.mf, b.mf);
		c.mpf = a.mpf;
		c.msf = b.msf;
	}
	c.mpn = a.mpn;
	c.msn = b.msn;
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
		T left = {0, 0, 0, 0, 0}, right = {0, 0, 0, 0, 0};
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) left = combine(left, ST[l++]);
			if(!(r & 1)) right = combine(ST[r--], right);
		}
		return combine(left, right);
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, q, x, l, r;
	while(cin >> n && n){
		cin >> q;
		SegmentTree<node> *st = new SegmentTree<node>(n);
		for(int i = 0; i < n; ++i){
			cin >> x;
			st->ST[n + i] = {1, 1, 1, x, x};
		}
		st->build();
		while(q--){
			cin >> l >> r;
			cout << st->query(l - 1, r - 1).mf << "\n";
		}
	}
	return 0;
}