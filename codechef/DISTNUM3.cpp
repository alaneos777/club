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

	int lca(int a, int b){
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		return a;
	}
};

int S = 0;

struct query{
	int l, r, time, index, p;
	query() {}
	query(int l, int r, int time, int index, int p = -1): l(l), r(r), time(time), index(index), p(p) {}
	bool operator<(const query & q) const{
		int leftLhs = l/S, leftRhs = q.l/S;
		if(leftLhs != leftRhs){
			return leftLhs < leftRhs;
		}else{
			int rightLhs = r/S, rightRhs = q.r/S;
			if(rightLhs != rightRhs){
				return rightLhs < rightRhs;
			}else{
				return time < q.time;
			}
		}
	}
};

struct update{
	int prev, next, u;
	update(){}
	update(int prev, int next, int u): prev(prev), next(next), u(u) {}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> weights(n), prev_weights;
	int sz_w = 0;
	map<int, int> ids;
	for(int i = 0; i < n; ++i){
		int w;
		cin >> w;
		if(ids.count(w) == 0){
			ids[w] = sz_w++;
		}
		weights[i] = ids[w];
	}
	HeavyLight hld(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		hld.adj[u-1].push_back(v-1);
		hld.adj[v-1].push_back(u-1);
	}

	vector<int> start(n), end(n), flat_idx(2*n);
	int tim = 0;
	function<void(int, int)> dfs = [&](int u, int p){
		start[u] = tim++;
		flat_idx[start[u]] = u;
		for(int v : hld.adj[u]){
			if(v == p) continue;
			dfs(v, u);
		}
		end[u] = tim++;
		flat_idx[end[u]] = u;
	};
	dfs(0, -1);
	hld.init(0);

	prev_weights = weights;
	vector<query> queries;
	vector<update> updates;
	for(int i = 0; i < m; ++i){
		int type, u, v;
		cin >> type >> u >> v;
		if(type == 1){
			--u, --v;
			if(start[u] > start[v]) swap(u, v);
			int p = hld.lca(u, v);
			if(p == u){
				queries.emplace_back(start[u], start[v], updates.size(), queries.size());
			}else{
				queries.emplace_back(end[u], start[v], updates.size(), queries.size(), p);
			}
		}else{
			--u;
			if(ids.count(v) == 0){
				ids[v] = sz_w++;
			}
			v = ids[v];
			updates.emplace_back(prev_weights[u], v, u);
			prev_weights[u] = v;
		}
	}

	S = 2*powl(n, 2.0l/3.0l);
	sort(queries.begin(), queries.end());
	vector<int> answers(queries.size());
	vector<int> freq_idx(n), freq_weight(sz_w);
	int prevL = 0, prevR = -1, updatesCnt = 0;
	int different = 0;

	auto remove = [&](int u){
		int& f1 = freq_idx[u];
		int& f2 = freq_weight[weights[u]];
		int prev = f2;
		f1--;
		if(f1 == 1) f2++;
		else if(f1 == 0) f2--;
		if(prev == 0 && f2 > 0) different++;
		else if(prev > 0 && f2 == 0) different--;
	};

	auto add = [&](int u){
		int& f1 = freq_idx[u];
		int& f2 = freq_weight[weights[u]];
		int prev = f2;
		f1++;
		if(f1 == 2) f2--;
		else if(f1 == 1) f2++;
		if(prev == 0 && f2 > 0) different++;
		else if(prev > 0 && f2 == 0) different--;
	};

	auto change = [&](int u, int next){
		if(freq_idx[u] == 1){
			remove(u);
			weights[u] = next;
			add(u);
		}
		weights[u] = next;
	};

	for(const query& q : queries){
		while(updatesCnt < q.time){
			change(updates[updatesCnt].u, updates[updatesCnt].next);
			updatesCnt++;
		}

		while(updatesCnt > q.time){
			updatesCnt--;
			change(updates[updatesCnt].u, updates[updatesCnt].prev);
		}

		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i) remove(flat_idx[i]);
		for(int i = prevL - 1; i >= q.l; --i) add(flat_idx[i]);
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i) add(flat_idx[i]);
		for(int i = prevR; i >= q.r + 1; --i) remove(flat_idx[i]);

		int ans = different;
		if(q.p != -1 && freq_weight[weights[q.p]] == 0){
			ans++;
		}
		answers[q.index] = ans;
		prevL = q.l, prevR = q.r;
	}

	for(int ans : answers){
		cout << ans << "\n";
	}
	return 0;
}