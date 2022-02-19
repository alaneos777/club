#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli inf = 1e18;

template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;

	SegmentTree(int N): N(N), ST(N<<1, -inf){}

	void update(int i, T value){
		ST[i += N] = value;
		while(i >>= 1)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}

	T query(int l, int r){
		T res = -inf;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = max(res, ST[l++]);
			if(!(r & 1)) res = max(res, ST[r--]);
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, x;
	cin >> n >> k >> x;
	vector<SegmentTree<lli>> st(x+1, SegmentTree<lli>(n+1));
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	a.insert(a.begin(), 0);
	st[x].update(0, 0);
	for(int pos = 1; pos <= n; ++pos){
		for(int rep = 0; rep < x; ++rep){
			lli c = st[rep+1].query(pos - min(k, pos), pos - 1);
			if(c != -inf) c += a[pos];
			st[rep].update(pos, c);
		}
	}
	lli ans = -inf;
	for(int j = 0; j <= x; ++j){
		ans = max(ans, st[j].query(n-k+1, n));
	}
	if(ans == -inf) ans = -1;
	cout << ans << "\n";
	return 0;
}