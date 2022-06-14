#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

using mat = vector<vector<int>>;

mat operator*(const mat& a, const mat& b){
	int n = a.size();
	mat c(n, vector<int>(n));
	for(int i = 0; i < n; ++i){
		for(int k = 0; k < n; ++k){
			for(int j = 0; j < n; ++j){
				c[i][j] += (lli)a[i][k] * b[k][j] % mod;
				if(c[i][j] >= mod) c[i][j] -= mod;
			}
		}
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	mat adj(n, vector<int>(n));
	while(m--){
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u][v] = 1;
		adj[v][u] = 1;
	}
	mat ans(n, vector<int>(n));
	for(int i = 0; i < n; ++i){
		ans[i][i] = 1;
	}
	while(k){
		if(k&1) ans = ans * adj;
		k >>= 1;
		adj = adj * adj;
	}
	int ways = 0;
	for(int v = 0; v < n; ++v){
		ways += ans[0][v];
		if(ways >= mod) ways -= mod;
	}
	cout << ways << "\n";
	return 0;
}