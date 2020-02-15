#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> d(n);
	for(int & di : d){
		cin >> di;
	}
	vector<vector<int>> adj(n);
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	int ans = -1;
	for(int i = 0; i < n; ++i){
		if(d[i] != 0) continue;
		bool test = true;
		for(int v : adj[i]){
			test = test & (d[v] == 1);
		}
		if(test) ans = i;
	}
	cout << ans+1 << "\n";
	return 0;
}