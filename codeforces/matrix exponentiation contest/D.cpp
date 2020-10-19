#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = int64_t;

const lli mod = 1e9 + 7;

using vec = vector<lli>;
using mat = vector<vec>;

mat operator*(const mat & a, const mat & b){
	int n = a.size();
	mat c(n, vec(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k){
				(c[i][j] += a[i][k] * b[k][j]) %= mod;
			}
		}
	}
	return c;
}

mat power(mat a, lli b){
	int n = a.size();
	mat ans(n, vec(n));
	for(int i = 0; i < n; ++i) ans[i][i] = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	mat a(n, vec(n));
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		a[u-1][v-1] = 1;
	}
	a = power(a, k);
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			(ans += a[i][j]) %= mod;
		}
	}
	cout << ans << "\n";
	return 0;
}