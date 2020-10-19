#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = int64_t;

const lli mod = 1e9 + 7;
using arr = array<lli, 4>;

arr get(char c){
	if(c == 'S' || c == 'D'){
		return {0, 1, 0, 1};
	}else if(c == 'H'){
		return {1, 0, 1, 0};
	}else if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
		return {0, 1, 1, 0};
	}else if(c == '?'){
		return {19, 7, 6, 20};
	}else{
		return {1, 0, 0, 1};
	}
}

arr operator*(const arr & a, const arr & b){
	return {
		(a[0]*b[0] + a[1]*b[2]) % mod,
		(a[0]*b[1] + a[1]*b[3]) % mod,
		(a[2]*b[0] + a[3]*b[2]) % mod,
		(a[2]*b[1] + a[3]*b[3]) % mod
	};
}

struct SegmentTree{
	int N;
	vector<arr> ST;

	SegmentTree(int N, const string & s): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i){
			ST[N + i] = get(s[i]);
		}
		for(int i = N - 1; i > 0; --i){
			ST[i] = ST[i << 1] * ST[i << 1 | 1];
		}
	}

	void update(int i, const arr & value){
		ST[i += N] = value;
		while(i >>= 1)
			ST[i] = ST[i << 1] * ST[i << 1 | 1];
	}

	arr query(int l, int r){
		arr lhs = {1, 0, 0, 1};
		arr rhs = lhs;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) lhs = lhs * ST[l++];
			if(!(r & 1)) rhs = ST[r--] * rhs;
		}
		return lhs * rhs;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	SegmentTree st(n, s);
	cout << st.query(0, n-1)[0] << "\n";
	while(q--){
		int i; char c;
		cin >> i >> c;
		st.update(i-1, get(c));
		cout << st.query(0, n-1)[0] << "\n";
	}
	return 0;
}