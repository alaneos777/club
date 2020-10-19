#include <bits/stdc++.h>
using namespace std;

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
	}

	void update(int i, int value){
		ST[i += N] += value;
		while(i >>= 1)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}

	int query(int l, int r){
		int res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = max(res, ST[l++]);
			if(!(r & 1)) res = max(ST[r--], res);
		}
		return res;
	}
};

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head, pos;
	int cur_pos;
	SegmentTree * st;

	HeavyLight(int n, SegmentTree * st): n(n), st(st){
		adj.resize(n);
		parent.resize(n);
		level.resize(n);
		size.resize(n);
		heavy.resize(n, -1);
		head.resize(n);
		pos.resize(n);
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
		pos[u] = cur_pos++;
		if(heavy[u] != -1) build(heavy[u], h);
		for(int v : adj[u])
			if(v != parent[u] && v != heavy[u])
				build(v, v);
	}

	void init(){
		cur_pos = 0;
		dfs(0);
		build(0, 0);
	}

	int query(int a, int b){
		int mx = 0;
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			mx = max(mx, st->query(pos[head[b]], pos[b]));
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		mx = max(mx, st->query(pos[a], pos[b]));
		return mx;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n;
	SegmentTree * st = new SegmentTree(n);
	HeavyLight hld(n, st);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		--u, --v;
		hld.adj[u].push_back(v);
		hld.adj[v].push_back(u);
	}
	hld.init();
	cin >> q;
	while(q--){
		char type; int u, v;
		cin >> type >> u >> v;
		if(type == 'I'){
			st->update(hld.pos[u-1], v);
		}else{
			cout << hld.query(u-1, v-1) << "\n";
		}
	}
	return 0;
}