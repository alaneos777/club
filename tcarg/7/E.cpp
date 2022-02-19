#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	int id = 0;
	vector<int> ids(n, -1);
	vector<vector<int>> out(n);
	function<void(int)> dfs = [&](int u){
		ids[u] = id;
		out[id].push_back(u);
		for(int v : adj[u]){
			if(ids[v] == -1){
				dfs(v);
			}
		}
	};
	for(int u = 0; u < n; ++u){
		if(ids[u] == -1){
			dfs(u);
			id++;
		}
	}
	bool cond = true;
	for(int i = 0; i < id; ++i){
		int sz = out[i].size();
		for(int u : out[i]){
			cond &= (adj[u].size() == sz-1);
		}
	}
	cout << (cond?"YES":"NO") << "\n";
	return 0;
}