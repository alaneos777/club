#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

struct dominator{
	int n;
	vector<vi> adj, tree, rad, buc;
	vi sdom, par, dom, dsu, lab, arr, rev;
	int cnt;

	dominator(int n): n(n){
		adj.resize(n+1), tree.resize(n+1), rad.resize(n+1), buc.resize(n+1), sdom.resize(n+1), par.resize(n+1), dom.resize(n+1), dsu.resize(n+1), lab.resize(n+1), arr.resize(n+1), rev.resize(n+1);
		cnt = 1;
		for (int i = 0; i <= n; i++) {
			sdom[i] = dsu[i] = lab[i] = i;
		}
	}

	void dfs (int u) {
		arr[u] = cnt, rev[cnt] = u, cnt++;

		for (int v : adj[u]) {
			if (!arr[v]) {
				dfs(v);
				par[arr[v]] = arr[u];
			}
			rad[arr[v]].push_back(arr[u]);
		}
	}

	int find (int u, int x = 0) {
		if (u == dsu[u])
			return x ? -1 : u;
		
		int v = find (dsu[u], x + 1);
		if (v < 0)
			return u;
		
		if (sdom[lab[dsu[u]]] < sdom[lab[u]])
			lab[u] = lab[dsu[u]];
		dsu[u] = v;

		return x ? v : lab[u];
	}

	void joint (int u, int v) {
		dsu[v] = u;
	}

	void obtDT () {
		dfs(1);

		for (int i = cnt - 1; i >= 1; i--) {
			for (int v : rad[i])
				sdom[i] = min(sdom[i], sdom[find(v)]);
			if (i > 1)
				buc[sdom[i]].push_back(i);

			for (int v : buc[i]) {
				int w = find(v);
				if (sdom[v] == sdom[w])
					dom[v] = sdom[v];
				else
					dom[v] = w;
			}

			if (i > 1)
				joint(par[i], i);
		}

		for (int i = 2; i < cnt; i++) {
			if (dom[i] != sdom[i])
				dom[i] = dom[dom[i]];
			tree[rev[i]].push_back(rev[dom[i]]);
			tree[rev[dom[i]]].push_back(rev[i]);
		}
	}

	vi nonTrivialDominators(){
		vi ans;
		function<bool(int, int)> dfs2 = [&](int u, int parent){
			bool has = false;
			for(int v : tree[u]){
				if(v == parent) continue;
				has = true;
				if(dfs2(v, u)) ans.push_back(v);
			}
			return has;
		};
		dfs2(1, -1);
		return ans;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, u, v;
	cin >> n >> m;
	dominator d(n+m), r(n+m);
	vector<pair<int, int>> edges(n+m+1);
	for(int i = 1; i <= m; ++i){
		cin >> u >> v;
		d.adj[u].push_back(n+i);
		d.adj[n+i].push_back(v);
		r.adj[n+i].push_back(u);
		r.adj[v].push_back(n+i);
		edges[n+i] = {u, v};
	}
	d.obtDT();
	r.obtDT();
	vi part1 = d.nonTrivialDominators();
	vi part2 = r.nonTrivialDominators();
	set<pair<int, int>> ans;
	for(int u : part1){
		if(n+1 <= u && u <= n+m) ans.insert(edges[u]);
	}
	for(int u : part2){
		if(n+1 <= u && u <= n+m) ans.insert(edges[u]);
	}
	cout << ans.size() << "\n";
	for(auto & edge : ans){
		cout << edge.first << " " << edge.second << "\n";
	}
	return 0;
}