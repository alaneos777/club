#include <bits/stdc++.h>
using namespace std;

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head;

	HeavyLight(int n): n(n){
		adj.resize(n);
		parent.resize(n), level.resize(n), size.resize(n);
		heavy.resize(n, -1), head.resize(n);
	}

	void dfs(int u){
		size[u] = 1;
		int mx = 0;
		for(int v : adj[u]){
			if(v != parent[u]){
				parent[v] = u;
				level[v] = level[u] + 1;
				dfs(v);
				if(size[v] > mx){
					mx = size[v];
					heavy[u] = v;
				}
				size[u] += size[v];
			}
		}
	}

	void build(int u, int h){
		head[u] = h;
		if(heavy[u] != -1) build(heavy[u], h);
		for(int v : adj[u])
			if(v != parent[u] && v != heavy[u])
				build(v, v);
	}

	void init(int root = 0){
		dfs(root);
		build(root, root);
	}

	int query(int a, int b){
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		return a;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	HeavyLight hld(n);
	for(int i = 1; i <= n-1; ++i){
		int p;
		cin >> p;
		hld.adj[i].push_back(p);
		hld.adj[p].push_back(i);
	}
	hld.init(0);
	while(q--){
		int u, v;
		cin >> u >> v;
		cout << hld.query(u, v) << "\n";
	}
	return 0;
}