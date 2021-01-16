#include <bits/stdc++.h>
using namespace std;

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head, pos, ipos;
	int cur_pos;;

	HeavyLight(int n): n(n){
		adj.resize(n), ipos.resize(n);
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

	int kth_ancestor(int u, int k){
		while(pos[u] - pos[head[u]] < k){
			k -= pos[u] - pos[head[u]] + 1;
			u = parent[head[u]];
		}
		return ipos[pos[u] - k];
	}
};

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
	}

	int query(int i){
		int res = ST[i += N];
		while(i >>= 1){
			res += ST[i];
		}
		return res;
	}

	void update(int l, int r, int value){
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) ST[l++] += value;
			if(!(r & 1)) ST[r--] += value;
		}
	}
};

const int mx = 1e5;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	HeavyLight hld(n);
	vector<int> age(n), ans(n);
	vector<vector<int>> parties(n);
	for(int i = 0; i < n; ++i){
		int parent;
		cin >> age[i] >> parent;
		--parent;
		if(i){
			hld.adj[parent].push_back(i);
			hld.adj[i].push_back(parent);
		}
	}
	hld.init();
	for(int i = 0; i < m; ++i){
		int u, l, r;
		cin >> u >> l >> r;
		--u;
		int left = 0, right = hld.level[u], owner = -1;
		while(left <= right){
			int k = (left + right) / 2;
			int v = hld.kth_ancestor(u, k);
			if(age[v] <= r){
				owner = v;
				left = k+1;
			}else{
				right = k-1;
			}
		}
		assert(owner != -1);
		parties[owner].push_back(l);
	}
	SegmentTree st(mx+1);
	function<void(int, int)> dfs = [&](int u, int p){
		for(int l : parties[u]){
			st.update(l, mx, 1);
		}
		ans[u] = st.query(age[u]);
		for(int v : hld.adj[u]){
			if(v == p) continue;
			dfs(v, u);
		}
		for(int l : parties[u]){
			st.update(l, mx, -1);
		}
	};
	dfs(0, -1);
	for(int i = 0; i < n; ++i){
		if(i) cout << " ";
		cout << ans[i];
	}
	cout << "\n";
	return 0;
}