#include <bits/stdc++.h>
using namespace std;

struct info{
	int open, closed, complete;
	info(): open(0), closed(0), complete(0) {}
	info(int a, int b, int c): open(a), closed(b), complete(c) {}
};

info combine(const info & i1, const info & i2){
	int a = i1.open + i2.open - min(i1.open, i2.closed);
	int b = i1.closed + i2.closed - min(i1.open, i2.closed);
	int c = i1.complete + i2.complete + min(i1.open, i2.closed);
	info d = info(a, b, c);
	return d;
}

struct SegmentTree{
	int N;
	vector<info> ST;

	SegmentTree(int N, string & str): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i] = info(str[i] == '(', str[i] == ')', 0);
		for(int i = N - 1; i > 0; --i)
			ST[i] = combine(ST[i << 1], ST[i << 1 | 1]);
	}

	info query(int l, int r){
		info resl, resr;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) resl = combine(resl, ST[l++]);
			if(!(r & 1)) resr = combine(ST[r--], resr);
		}
		return combine(resl, resr);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string str;
	cin >> str;
	SegmentTree st(str.size(), str);
	int m, l, r;
	cin >> m;
	while(m--){
		cin >> l >> r;
		cout << (2 * st.query(l-1, r-1).complete) << "\n";
	}
	return 0;
}