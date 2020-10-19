#include <bits/stdc++.h>
using namespace std;

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head, pos, ipos;
	int cur_pos;
	vector<int64_t> acum;

	HeavyLight(int n): n(n){
		adj.resize(n);
		parent.resize(n), level.resize(n), size.resize(n);
		heavy.resize(n, -1), head.resize(n), pos.resize(n), ipos.resize(n);
		acum.resize(n);
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
		pos[u] = cur_pos;
		ipos[cur_pos++] = u;
		if(heavy[u] != -1) build(heavy[u], h);
		for(int v : adj[u])
			if(v != parent[u] && v != heavy[u])
				build(v, v);
	}

	void init(int root = 0){
		cur_pos = 0;
		dfs(root);
		build(root, root);
	}

	inline int64_t get(int a, int b){
		return acum[b] - (a ? acum[a-1] : 0);
	}

	int64_t query(int a, int b){
		int64_t sum = 0;
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			sum += get(pos[head[b]], pos[b]);
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		if(pos[a] + 1 <= pos[b]) sum += get(pos[a] + 1, pos[b]);
		return sum;
	}

	int lca(int a, int b){
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		return a;
	}

	int kth_ancestor(int u, int k){
		while(pos[u] - pos[head[u]] < k){
			k -= pos[u] - pos[head[u]] + 1;
			u = parent[head[u]];
		}
		return ipos[pos[u] - k];
	}
};

using edge = tuple<int, int, int>;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		HeavyLight hld(n);
		vector<edge> edges;
		for(int i = 0; i < n-1; ++i){
			int u, v, w;
			cin >> u >> v >> w; --u, --v;
			hld.adj[u].push_back(v);
			hld.adj[v].push_back(u);
			edges.emplace_back(u, v, w);
		}
		hld.init();
		for(const edge & e : edges){
			int u, v, w;
			tie(u, v, w) = e;
			if(hld.parent[v] == u){
				hld.acum[hld.pos[v]] = w;
			}else{
				hld.acum[hld.pos[u]] = w;
			}
		}
		for(int i = 1; i < n; ++i){
			hld.acum[i] += hld.acum[i-1];
		}
		string q;
		while(true){
			cin >> q;
			if(q == "DIST"){
				int a, b;
				cin >> a >> b; --a, --b;
				cout << hld.query(a, b) << "\n";
			}else if(q == "KTH"){
				int a, b, k;
				cin >> a >> b >> k; --a, --b;
				int l = hld.lca(a, b);
				if(k <= hld.level[a] - hld.level[l] + 1){
					cout << hld.kth_ancestor(a, k-1) + 1 << "\n";
				}else{
					k = hld.level[a] + hld.level[b] - 2*hld.level[l] + 1 - k;
					cout << hld.kth_ancestor(b, k) + 1 << "\n";
				}
			}else{
				break;
			}
		}
	}
	return 0;
}