#include <bits/stdc++.h>
using namespace std;

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;

	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	int equalTo(int l, int r, int k){
		if(l > r || k < lo || k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		int m = (lo + hi) / 2;
		if(k <= m) return left->equalTo(lb + 1, rb, k);
		else return right->equalTo(l - lb, r - rb, k);
	}
};

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head, pos;
	int cur_pos;
	WaveletTree * st;

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

	bool query(int a, int b, int c){
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			if(st->equalTo(pos[head[b]]+1, pos[b]+1, c) > 0) return true;
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		if(st->equalTo(pos[a]+1, pos[b]+1, c) > 0) return true;
		return false;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	while(cin >> n >> m){
		vector<int> vals(n);
		for(int & v : vals){
			cin >> v;
		}
		HeavyLight hld(n);
		for(int i = 0; i < n-1; ++i){
			int u, v;
			cin >> u >> v;
			--u, --v;
			hld.adj[u].push_back(v);
			hld.adj[v].push_back(u);
		}
		hld.init();
		vector<int> pi(n);
		for(int i = 0; i < n; ++i){
			pi[hld.pos[i]] = vals[i];
		}
		WaveletTree st(pi.begin(), pi.end(), 0, *max_element(pi.begin(), pi.end()));
		hld.st = &st;
		while(m--){
			int u, v, w;
			cin >> u >> v >> w;
			cout << (hld.query(u-1, v-1, w) ? "Find" : "NotFind") << "\n";
		}
		cout << "\n";
	}
	return 0;
}