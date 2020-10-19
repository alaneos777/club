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

int main(){
	ofstream fout(getenv("OUTPUT_PATH"));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, r;
	cin >> n >> m >> r;
	--r;
	vector<vector<int>> adj(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int> color(n);
	for(int & ci : color){
		cin >> ci;
	}

	vector<int> start(n), end(n), arr(2*n);
	int pos = 0;
	function<void(int, int)> dfs = [&](int u, int p){
		start[u] = pos;
		arr[pos] = color[u];
		pos++;
		for(int v : adj[u]){
			if(v == p) continue;
			dfs(v, u);
		}
		end[u] = pos;
		arr[pos] = color[u];
		pos++;
	};
	dfs(r, -1);

	vector<int> next(2*n);
	unordered_map<int, int> last;
	for(int i = 2*n-1; i >= 0; --i){
		if(last.count(arr[i]) == 0){
			next[i] = 2*n;
		}else{
			next[i] = last[arr[i]];
		}
		last[arr[i]] = i;
	}

	WaveletTree wt(next.begin(), next.end(), 0, 2*n);

	while(m--){
		int s;
		cin >> s; --s;
		int l = start[s], r = end[s];
		fout << r-l+1 - wt.lessThanOrEqual(l+1, r+1, r) << "\n";
	}
	return 0;
}