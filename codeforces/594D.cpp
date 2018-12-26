#include <bits/stdc++.h>
using namespace std;

using lli = long long int;
const lli mod = 1e9 + 7;

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(int N): N(N){
		ST.assign(N << 1, 1);
	}

	void build(vector<int> & arr){
		for(int i = 0; i < N; ++i)
			ST[N + i] = arr[i];
		for(int i = N - 1; i > 0; --i)
			ST[i] = (lli)ST[i << 1] * ST[i << 1 | 1] % mod;
	}

	int query(int l, int r){
		int res = 1;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = (lli)res * ST[l++] % mod;
			if(!(r & 1)) res = (lli)res * ST[r--] % mod;
		}
		return res;
	}

	void update(int i, int value){
		i += N;
		ST[i] = (lli)value * ST[i] % mod;
		while(i >>= 1)
			ST[i] = (lli)ST[i << 1] * ST[i << 1 | 1] % mod;
	}
};

const int M = 1e6 + 10;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

vector<int> lp;
void sieve(int n){
	lp.resize(n + 1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lp[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lp[j] == j) lp[j] = i;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(M);
	vector<int> inv(M + 1);
	for(int i = 1; i <= M; ++i){
		inv[i] = powerMod(i, mod - 2, mod);
	}
	int n, q, l, r;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a) cin >> ai;
	cin >> q;
	vector<vector<pair<int, int>>> queries(n);
	vector<int> answers(q);
	for(int i = 0; i < q; ++i){
		cin >> l >> r;
		--l, --r;
		queries[r].emplace_back(l, i);
	}
	SegmentTree st_prods(n), st_primes(n);
	st_prods.build(a);
	vector<int> tmp(M + 1, -1);
	for(int r = 0; r < n; ++r){
		int x = a[r];
		while(x > 1){
			int p = lp[x];
			while(x % p == 0) x /= p;
			if(tmp[p] != -1) st_primes.update(tmp[p], (lli)p * inv[p-1] % mod);
			st_primes.update(r, (lli)(p - 1) * inv[p] % mod);
			tmp[p] = r;
		}
		for(auto & query : queries[r]){
			int l, i;
			tie(l, i) = query;
			int B = st_primes.query(l, r);
			int C = st_prods.query(l, r);
			answers[i] = (lli)C * B % mod;
		}
	}
	for(int & ans : answers){
		cout << ans << "\n";
	}
	return 0;
}