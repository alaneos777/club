#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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
	int l, r, index, f;
	int64_t ord;
	query() {}
	query(int l, int r, int f, int index): l(l), r(r), f(f), index(index) {
		ord = gilbertOrder(l, r, 21, 0);
	}
	bool operator<(const query & q) const{
		return ord < q.ord;
	}
};

inline lli sq(lli x){
	return x*x;
}

struct SegmentTree{
	int N;
	vector<lli> ST;

	SegmentTree(int N): N(N), ST(N << 1){}

	void update(int i, lli value){
		ST[i += N] += value;
		while(i >>= 1)
			ST[i] = ST[i << 1] + ST[i << 1 | 1];
	}

	lli query(int l, int r){
		lli res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res += ST[l++];
			if(!(r & 1)) res += ST[r--];
		}
		return res;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n;
	vector<int> C(n), H(n);
	map<int, int> ids;
	int sz = 0;
	for(int i = 0; i < n; ++i){
		int ci;
		cin >> ci;
		if(ids.count(ci) == 0) ids[ci] = sz++;
		C[i] = ids[ci];
	}
	for(int& h : H) cin >> h;
	HeavyLight hld(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		hld.adj[u-1].push_back(v-1);
		hld.adj[v-1].push_back(u-1);
	}

	vector<int> start(n), end(n), flat_idx(2*n), flat_c(2*n), flat_h(2*n);
	int tim = 0;
	function<void(int, int)> dfs = [&](int u, int p){
		start[u] = tim;
		flat_idx[tim] = u;
		flat_c[tim] = C[u];
		flat_h[tim] = H[u];
		tim++;
		for(int v : hld.adj[u]){
			if(v == p) continue;
			dfs(v, u);
		}
		end[u] = tim;
		flat_idx[tim] = u;
		flat_c[tim] = C[u];
		flat_h[tim] = H[u];
		tim++;
	};
	dfs(0, -1);
	hld.init(0);

	cin >> m;
	vector<query> queries;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		--u, --v;
		if(start[u] > start[v]) swap(u, v);
		int p = hld.lca(u, v);
		if(p == u){
			queries.emplace_back(start[u], start[v], C[p], i);
		}else{
			queries.emplace_back(end[u], start[v], C[p], i);
		}
	}

	sort(queries.begin(), queries.end());
	vector<lli> answers(m);
	vector<int> freq_idx(n);
	vector<deque<int>> colors(sz);
	int prevL = 0, prevR = -1;
	SegmentTree st(sz);
	for(const query& q : queries){
		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			int& f1 = freq_idx[flat_idx[i]];
			auto& dq = colors[flat_c[i]];
			f1--;
			if(f1 == 1){
				dq.push_front(flat_h[i]);
				if(dq.size() > 1) st.update(flat_c[i], sq(dq[0] - dq[1]));
			}else if(f1 == 0){
				if(dq.size() > 1) st.update(flat_c[i], -sq(dq[0] - dq[1]));
				dq.pop_front();
			}
		}
		for(int i = prevL - 1; i >= q.l; --i){
			int& f1 = freq_idx[flat_idx[i]];
			auto& dq = colors[flat_c[i]];
			f1++;
			if(f1 == 2){
				if(dq.size() > 1) st.update(flat_c[i], -sq(dq[0] - dq[1]));
				dq.pop_front();
			}else if(f1 == 1){
				dq.push_front(flat_h[i]);
				if(dq.size() > 1) st.update(flat_c[i], sq(dq[0] - dq[1]));
			}
		}
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i){
			int& f1 = freq_idx[flat_idx[i]];
			auto& dq = colors[flat_c[i]];
			f1++;
			if(f1 == 2){
				if(dq.size() > 1) st.update(flat_c[i], -sq(dq[dq.size()-1] - dq[dq.size()-2]));
				dq.pop_back();
			}else if(f1 == 1){
				dq.push_back(flat_h[i]);
				if(dq.size() > 1) st.update(flat_c[i], sq(dq[dq.size()-1] - dq[dq.size()-2]));
			}
		}
		for(int i = prevR; i >= q.r + 1; --i){
			int& f1 = freq_idx[flat_idx[i]];
			auto& dq = colors[flat_c[i]];
			f1--;
			if(f1 == 1){
				dq.push_back(flat_h[i]);
				if(dq.size() > 1) st.update(flat_c[i], sq(dq[dq.size()-1] - dq[dq.size()-2]));
			}else if(f1 == 0){
				if(dq.size() > 1) st.update(flat_c[i], -sq(dq[dq.size()-1] - dq[dq.size()-2]));
				dq.pop_back();
			}
		}
		answers[q.index] = st.ST[1] - st.query(q.f, q.f);
		prevL = q.l, prevR = q.r;
	}

	for(lli ans : answers){
		cout << ans << "\n";
	}

	return 0;
}