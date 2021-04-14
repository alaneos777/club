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
	int l, r, index;
	int64_t ord;
	query() {}
	query(int l, int r, int index): l(l), r(r), index(index) {
		ord = gilbertOrder(l, r, 21, 0);
	}
	bool operator<(const query & q) const{
		return ord < q.ord;
	}
};

using tup = tuple<int, int, int>;
const int inf = 2e9;

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(const vector<int> & arr): N(arr.size()){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i] = arr[i];
		for(int i = N - 1; i > 0; --i)
			ST[i] = min(ST[i << 1], ST[i << 1 | 1]);
	}

	void update(int i, int value){
		ST[i += N] = value;
		while(i >>= 1){
			ST[i] = min(ST[i << 1], ST[i << 1 | 1]);
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	HeavyLight hld(n);
	vector<tup> edges;
	vector<int> nums = {0};
	for(int i = 0; i < n-1; ++i){
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		hld.adj[u].push_back(v);
		hld.adj[v].push_back(u);
		edges.emplace_back(u, v, w);
		if(w) nums.push_back(w-1);
		nums.push_back(w); nums.push_back(w+1);
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

	vector<int> val(n);
	for(const auto& [u, v, w] : edges){
		if(hld.parent[u] == v){
			val[u] = w;
		}else{
			val[v] = w;
		}
	}

	vector<query> queries;
	for(int i = 0; i < q; ++i){
		int u, v;
		cin >> u >> v;
		--u, --v;
		if(start[u] > start[v]) swap(u, v);
		int p = hld.lca(u, v);
		if(p == u){
			queries.emplace_back(start[u]+1, start[v], i);
		}else{
			queries.emplace_back(end[u], start[v], i);
		}
	}
	sort(queries.begin(), queries.end());
	
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	unordered_map<int, int> mp;
	for(int i = 0; i < nums.size(); ++i) mp[nums[i]] = i;
	vector<int> mp2(n), freq(nums.size());
	for(int i = 0; i < n; ++i) mp2[i] = mp[val[i]];
	SegmentTree st(nums);

	vector<int> freq_idx(n);
	vector<int> answers(q);
	int prevL = 0, prevR = -1;

	auto remove = [&](int u){
		int& f1 = freq_idx[u];
		f1--;
		if(f1 == 1) freq[mp2[u]]++, st.update(mp2[u], inf);
		else if(f1 == 0){
			freq[mp2[u]]--;
			if(freq[mp2[u]] == 0) st.update(mp2[u], val[u]);
		}
	};

	auto add = [&](int u){
		int& f1 = freq_idx[u];
		f1++;
		if(f1 == 2){
			freq[mp2[u]]--;
			if(freq[mp2[u]] == 0) st.update(mp2[u], val[u]);
		}
		else if(f1 == 1) freq[mp2[u]]++, st.update(mp2[u], inf);
	};

	for(const query& q : queries){
		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i) remove(flat_idx[i]);
		for(int i = prevL - 1; i >= q.l; --i) add(flat_idx[i]);
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i) add(flat_idx[i]);
		for(int i = prevR; i >= q.r + 1; --i) remove(flat_idx[i]);
		prevL = q.l, prevR = q.r;
		answers[q.index] = st.ST[1];
	}

	for(int ans : answers){
		cout << ans << "\n";
	}
	return 0;
}