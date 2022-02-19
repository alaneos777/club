#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	vector<int> sz(n);
	int ans = 0;
	function<void(int, int)> dfs = [&](int u, int p){
		sz[u] = 1;
		for(int v : adj[u]){
			if(v == p) continue;
			dfs(v, u);
			sz[u] += sz[v];
		}
		if(sz[u]%2 == 0){
			if(p != -1) ans++;
		}
	};
	dfs(0, -1);
	if(n%2==0) cout << ans << "\n";
	else cout << "-1\n";
	return 0;
}