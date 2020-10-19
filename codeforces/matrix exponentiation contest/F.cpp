#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = int64_t;

using vec = vector<lli>;
using mat = vector<vec>;

const lli inf = numeric_limits<lli>::max();

mat operator*(const mat & a, const mat & b){
	int n = a.size();
	mat c(n, vec(n, inf));
	for(int k = 0; k < n; ++k){
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(a[i][k] != inf && b[k][j] != inf){
					c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
				}
			}
		}
	}
	return c;
}

mat power(mat a, lli b){
	int n = a.size();
	mat ans(n, vec(n, inf));
	for(int i = 0; i < n; ++i) ans[i][i] = 0;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m; lli k;
	cin >> n >> m >> k;
	mat adj(n, vec(n, inf));
	while(m--){
		int u, v; lli c;
		cin >> u >> v >> c;
		adj[u-1][v-1] = c;
	}
	adj = power(adj, k);
	lli ans = inf;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			ans = min(ans, adj[i][j]);
		}
	}
	if(ans == inf) cout << "IMPOSSIBLE\n";
	else cout << ans << "\n";
	return 0;
}