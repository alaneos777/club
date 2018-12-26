#include <bits/stdc++.h>
using namespace std;

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;

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

	int lessThanOrEqual(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		return left->lessThanOrEqual(lb + 1, rb, k) + right->lessThanOrEqual(l - lb, r - rb, k);
	}
};

using vi = vector<int>;

struct tree{
	vi parent, level;
	vector<vi> DP, adj;
	int n, root;

	tree(int n, int root): n(n), root(root), parent(n), level(n), DP(n, vi(20)){
		parent[root] = root;
	}

	void dfs(int u){
		for(int v : adj[u]){
			if(v != parent[u]){
				level[v] = level[u] + 1;
				dfs(v);
			}
		}
	}

	void pre(){
		for(int u = 0; u < n; u++){
			DP[u][0] = parent[u];
		}
		for(int i = 1; (1 << i) <= n; ++i){
			for(int u = 0; u < n; ++u){
				DP[u][i] = DP[DP[u][i - 1]][i - 1];
			}
		}
	}

	int ancestor(int p, int k){
		int h = level[p] - k;
		if(h < 0) return 0;
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= h){
				p = DP[p][i];
			}
		}
		return p;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, q, l, r, last = 0;
	cin >> n >> k;
	vector<int> a(n), b(n);
	for(int & ai : a){
		cin >> ai;
	}
	vector<int> prev(n+1, 0), tmp(100000+10, 0);
	for(int i = 1; i <= n; ++i){
		if(tmp[a[i-1]] != 0) prev[i] = tmp[a[i-1]];
		tmp[a[i-1]] = i;
	}

	vector<vector<int>> adj(n+1);
	for(int i = 1; i <= n; ++i){
		adj[i].push_back(prev[i]);
		adj[prev[i]].push_back(i);
	}

	tree tr(n+1, 0);
	tr.adj = adj;
	tr.parent = prev;
	tr.dfs(0);
	tr.pre();
	for(int i = 0; i < n; ++i){
		b[i] = tr.ancestor(i+1, k);
	}
	WaveletTree w(b.begin(), b.end(), 0, *max_element(b.begin(), b.end()));
	cin >> q;
	while(q--){
		cin >> l >> r;
		l = (l + last) % n + 1;
		r = (r + last) % n + 1;
		if(l > r) swap(l, r);
		cout << (last = w.lessThanOrEqual(l, r, l-1)) << "\n";
	}
	return 0;
}