#include <bits/stdc++.h>
using namespace std;

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
			ST[i] = min(ST[i << 1], ST[i << 1 | 1]);
	}

	//single element update in pos
	void update(int pos, T value){
		ST[pos += N] = value;
		while(pos >>= 1)
			ST[pos] = min(ST[pos << 1], ST[pos << 1 | 1]);
	}

	//range query, [l, r]
	T query(int l, int r){
		T res = 2e9;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) res = min(res, ST[l++]);
			if(!(r & 1)) res = min(res, ST[r--]);
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, l;
	cin >> n >> l;
	SegmentTree<int> st(n);
	for(int i = 0; i < n; ++i){
		cin >> st.ST[n + i];
	}
	st.build();
	for(int a = 0, b = l-1; b < n; ++a, ++b){
		if(a) cout << " ";
		cout << st.query(a, b);
	}cout << "\n";
	return 0;
}