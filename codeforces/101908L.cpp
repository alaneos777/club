#include <bits/stdc++.h>
using namespace std;

struct SegmentTreeDin{
	SegmentTreeDin *left, *right;
	int l, r;
	int sum, lazy;
 
	SegmentTreeDin(int start, int end): left(NULL), right(NULL), l(start), r(end), sum(0), lazy(0){
		if(l == r) sum = 0;
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTreeDin(l, half);
			right = new SegmentTreeDin(half+1, r);
			sum = left->sum + right->sum;
		}
	}
 
	void propagate(int dif){
		sum += (r - l + 1) * dif;
		if(l != r){
			left->lazy += dif;
			right->lazy += dif;
		}
	}
 
	int sum_query(int start, int end){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else return left->sum_query(start, end) + right->sum_query(start, end);
	}
 
	void add_range(int start, int end, int dif){
		if(lazy != 0){
			propagate(lazy);
			lazy = 0;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(dif);
		else{
			left->add_range(start, end, dif);
			right->add_range(start, end, dif);
			sum = left->sum + right->sum;
		}
	}
};

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head, pos;
	int cur_pos;
	SegmentTreeDin * st;

	HeavyLight(int n): n(n){
		adj.resize(n);
		parent.resize(n), level.resize(n), size.resize(n);
		heavy.resize(n, -1), head.resize(n), pos.resize(n);
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
		int sum = 0;
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			sum += st->sum_query(pos[head[b]], pos[b]);
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		sum += st->sum_query(pos[a], pos[b]);
		return sum;
	}

	void add(int a, int b, int x){
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			st->add_range(pos[head[b]], pos[b], x);
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		st->add_range(pos[a], pos[b], x);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	HeavyLight hld(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		hld.adj[u-1].push_back(v-1);
		hld.adj[v-1].push_back(u-1);
	}
	hld.init();
	hld.st = new SegmentTreeDin(0, n-1);
	while(q--){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		--a, --b, --c, --d;
		hld.add(a, b, 1);
		cout << hld.query(c, d) << "\n";
		hld.add(a, b, -1);
	}
	return 0;
}