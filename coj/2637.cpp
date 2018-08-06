#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;

	SegmentTree(int N){
		this->N = N;
		ST.assign(N << 1, 0);
	}

	void build(){
		for(int i = N - 1; i > 0; --i)
			ST[i] = ST[i << 1] + ST[i << 1 | 1];
	}

	void update(int pos, T value){
		ST[pos += N] = value;
		while(pos >>= 1)
			ST[pos] = ST[pos << 1] + ST[pos << 1 | 1];
	}

	T query(int l, int r){
		++r;
		T res = 0;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res += ST[l++];
			if(r & 1) res += ST[--r];
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t, n, q, l, r;
	cin >> t;
	for(int c = 1; c <= t; ++c){
		if(c > 1) cout << "\n";
		cin >> n >> q;
		SegmentTree<lli> * st = new SegmentTree<lli>(n);
		for(int i = 0; i < n; ++i){
			cin >> st->ST[n + i];
		}
		st->build();
		while(q--){
			cin >> l >> r;
			cout << st->query(l, r) << "\n";
		}
	}
}