#include <bits/stdc++.h>
using namespace std;

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(int N, vector<int> & arr): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i] = arr[i];
		for(int i = N - 1; i > 0; --i)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}

	void update(int i, int value){
		ST[i += N] = value;
		while(i >>= 1)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}

	int query(int l, int r){
		int res = -1e9;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = max(res, ST[l++]);
			if(!(r & 1)) res = max(ST[r--], res);
		}
		return res;
	}
};

struct HeavyLight{
	int n;
	vector< vector<int> > adj;
	vector<int> parent, level, size, heavy, head, pos;
	int cur_pos;
	SegmentTree * st;

	HeavyLight(int n): n(n){
		adj.resize(n);
		parent.resize(n), level.resize(n), size.resize(n);
		heavy.resize(n, -1), head.resize(n), pos.resize(n);
	}

	void dfs(int u){
		size[u] = 1;
		int mx = 0;
		for(int i = 0; i < adj[u].size(); ++i){
			int v = adj[u][i];
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
		for(int i = 0; i < adj[u].size(); ++i){
			int v = adj[u][i];
			if(v != parent[u] && v != heavy[u])
				build(v, v);
		}
	}

	void init(){
		cur_pos = 0;
		dfs(0);
		build(0, 0);
	}

	int query(int a, int b){
		int mx = -1e9;
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			mx = max(mx, st->query(pos[head[b]], pos[b]));
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		if(pos[a] + 1 <= pos[b]) mx = max(mx, st->query(pos[a] + 1, pos[b]));
		return mx;
	}
};

struct edge{
	int u, v, w;
	edge(int u, int v, int w): u(u), v(v), w(w) {}
};

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
			cin >> u >> v >> w;
			--u, --v;
			hld.adj[u].push_back(v);
			hld.adj[v].push_back(u);
			edges.push_back(edge(u, v, w));
		}
		hld.init();
		vector<int> arr(n);
		for(int i = 0; i < n-1; ++i){
			int u = edges[i].u, v = edges[i].v, w = edges[i].w;
			if(hld.parent[v] == u){
				arr[hld.pos[v]] = w;
			}else{
				arr[hld.pos[u]] = w;
			}
		}
		hld.st = new SegmentTree(n, arr);
		string q;
		while(true){
			cin >> q;
			if(q == "DONE") break;
			else if(q == "QUERY"){
				int a, b;
				cin >> a >> b;
				--a, --b;
				cout << hld.query(a, b) << "\n";
			}else{
				int i, ti;
				cin >> i >> ti;
				int u = edges[i-1].u, v = edges[i-1].v;
				if(hld.parent[v] == u){
					hld.st->update(hld.pos[v], ti);
				}else{
					hld.st->update(hld.pos[u], ti);
				}
			}
		}
	}
	return 0;
}