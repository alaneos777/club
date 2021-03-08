#include <bits/stdc++.h>
using namespace std;

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head;
	int cur_pos;

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

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct query{
	int l, r, index, p;
	int64_t ord;
	query() {}
	query(int l, int r, int index, int p = -1): l(l), r(r), index(index), p(p) {
		ord = gilbertOrder(l, r, 21, 0);
	}
	bool operator<(const query & q) const{
		return ord < q.ord;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	while(cin >> n >> m){
		vector<int> weights(n);
		int id_w = 0;
		map<int, int> ids;
		for(int i = 0; i < n; ++i){
			int w;
			cin >> w;
			if(ids.count(w) == 0){
				ids[w] = id_w++;
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

		vector<int> start(n), end(n), flat_idx(2*n), flat_weight(2*n);
		int tim = 0;
		function<void(int, int)> dfs = [&](int u, int p){
			start[u] = tim++;
			flat_idx[start[u]] = u;
			flat_weight[start[u]] = weights[u];
			for(int v : hld.adj[u]){
				if(v == p) continue;
				dfs(v, u);
			}
			end[u] = tim++;
			flat_idx[end[u]] = u;
			flat_weight[end[u]] = weights[u];
		};
		dfs(0, -1);
		hld.init(0);

		vector<query> queries;
		for(int i = 0; i < m; ++i){
			int u, v;
			cin >> u >> v;
			--u, --v;
			if(start[u] > start[v]) swap(u, v);
			int p = hld.lca(u, v);
			if(p == u){
				queries.emplace_back(start[u], start[v], i);
			}else{
				queries.emplace_back(end[u], start[v], i, start[p]);
			}
		}

		sort(queries.begin(), queries.end());
		vector<int> answers(m);
		vector<int> freq_idx(n), freq_weight(n);
		int prevL = 0, prevR = -1;
		int different = 0;
		for(const query & q : queries){
			for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
				int& f1 = freq_idx[flat_idx[i]];
				int& f2 = freq_weight[flat_weight[i]];
				int prev = f2;
				f1--;
				if(f1 == 1) f2++;
				else if(f1 == 0) f2--;
				if(prev == 0 && f2 > 0) different++;
				else if(prev > 0 && f2 == 0) different--;
			}
			for(int i = prevL - 1; i >= q.l; --i){
				int& f1 = freq_idx[flat_idx[i]];
				int& f2 = freq_weight[flat_weight[i]];
				int prev = f2;
				f1++;
				if(f1 == 2) f2--;
				else if(f1 == 1) f2++;
				if(prev == 0 && f2 > 0) different++;
				else if(prev > 0 && f2 == 0) different--;
			}
			for(int i = max(prevR + 1, q.l); i <= q.r; ++i){
				int& f1 = freq_idx[flat_idx[i]];
				int& f2 = freq_weight[flat_weight[i]];
				int prev = f2;
				f1++;
				if(f1 == 2) f2--;
				else if(f1 == 1) f2++;
				if(prev == 0 && f2 > 0) different++;
				else if(prev > 0 && f2 == 0) different--;
			}
			for(int i = prevR; i >= q.r + 1; --i){
				int& f1 = freq_idx[flat_idx[i]];
				int& f2 = freq_weight[flat_weight[i]];
				int prev = f2;
				f1--;
				if(f1 == 1) f2++;
				else if(f1 == 0) f2--;
				if(prev == 0 && f2 > 0) different++;
				else if(prev > 0 && f2 == 0) different--;
			}
			int ans = different;
			if(q.p != -1 && freq_weight[flat_weight[q.p]] == 0){
				ans++;
			}
			answers[q.index] = ans;
			prevL = q.l, prevR = q.r;
		}

		for(int ans : answers){
			cout << ans << "\n";
		}
	}
	return 0;
}