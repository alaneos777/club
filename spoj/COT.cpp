#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
 
int M;
bool f(int x){return x <= M;}
 
struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;
 
	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		M = (lo + hi) / 2;
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for(vector<int>::iterator it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
		}
		if(hi != lo){
			vector<int>::iterator pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, M);
			right = new WaveletTree(pivot, to, M + 1, hi);
		}
	}
 
	int lessThanOrEqual(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		return left->lessThanOrEqual(lb + 1, rb, k) + right->lessThanOrEqual(l - lb, r - rb, k);
	}
};
 
struct HeavyLight{
	int n;
	vector< vector<int> > adj;
	vector<int> parent, level, size, heavy, head, pos;
	int cur_pos;
	WaveletTree * wt;
 
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
 
	void init(int root = 0){
		cur_pos = 0;
		dfs(root);
		build(root, root);
	}
 
	int query(const vector< pair<int, int> > & ranges, int k){
		int l = 0, r = n-1, ans = -1;
		while(l <= r){
			int x = (l + r) >> 1;
			int leq = 0;
			for(int i = 0; i < ranges.size(); ++i){
				leq += wt->lessThanOrEqual(ranges[i].first+1, ranges[i].second+1, x);
			}
			if(leq >= k){
				ans = x;
				r = x-1;
			}else{
				l = x+1;
			}
		}
		return ans;
	}
 
	int query(int a, int b, int k){
		vector< pair<int, int> > ranges;
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			ranges.push_back(make_pair(pos[head[b]], pos[b]));
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		ranges.push_back(make_pair(pos[a], pos[b]));
		return query(ranges, k);
	}
};
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector< pair<lli, int> > weights(n);
	vector<int> order(n);
	for(int i = 0; i < n; ++i){
		cin >> weights[i].first;
		weights[i].second = i;
	}
	sort(weights.begin(), weights.end());
	for(int i = 0; i < n; ++i){
		order[weights[i].second] = i;
	}
	HeavyLight hld(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		hld.adj[u-1].push_back(v-1);
		hld.adj[v-1].push_back(u-1);
	}
	hld.init();
	vector<int> order_hld(n);
	for(int i = 0; i < n; ++i){
		order_hld[hld.pos[i]] = order[i];
	}
	WaveletTree *wt = new WaveletTree(order_hld.begin(), order_hld.end(), 0, n-1);
	hld.wt = wt;
	while(m--){
		int u, v, k;
		cin >> u >> v >> k;
		int res = hld.query(u-1, v-1, k);
		cout << weights[res].first << "\n";
	}
	return 0;
}