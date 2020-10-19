#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct SegmentTree{
	int N;
	vector<int> ST;
	vector<pair<int, int>> range;
	vector<ordered_set<int>> positions;

	//build from an array in O(n)
	SegmentTree(int N): N(N){
		ST.resize(N << 1, -1);
		range.resize(N << 1);
        positions.resize(1e5 + 1);
		for(int i = 0; i < N; ++i)
			range[N + i] = {i, i};
		for(int i = N - 1; i > 0; --i)
			range[i] = {range[i << 1].first, range[i << 1 | 1].second};
	}

	int getCnt(int x, int l, int r){
		if(positions[x].empty()) return 0;
		int L = positions[x].order_of_key(l);
		if(L == positions[x].size()) return 0;
		int R = positions[x].order_of_key(r+1);
		return R - L;
	}

	int combine(int a, int b, int l, int r){
		if(ST[a] != -1 && 2*getCnt(ST[a], l, r) > r - l + 1){
			return ST[a];
		}else if(ST[b] != -1 && 2*getCnt(ST[b], l, r) > r - l + 1){
			return ST[b];
		}else{
			return -1;
		}
	}

	void update(int i, int old, int value){
		ST[i + N] = value;
		if(old != -1) positions[old].erase(i);
		positions[value].insert(i);
		i += N;
		while(i >>= 1){
			ST[i] = combine(i << 1, i << 1 | 1, range[i].first, range[i].second);
		}
	}

	pair<int, int> get(int a, const vector<pair<int, int>> & ranges){
		if(ST[a] == -1) return {-1, 0};
		int cnt = 0, len = 0;
		for(const auto & par : ranges){
			cnt += getCnt(ST[a], par.first, par.second);
			len += par.second - par.first + 1;
		}
		if(2*cnt > len) return {ST[a], cnt};
		return {-1, 0};
	}

	pair<int, int> query(int l, int r, const vector<pair<int, int>> & ranges){
		pair<int, int> res = {-1, 0};
		int L = l, R = r;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				auto tmp = get(l++, ranges);
				if(tmp.first != -1){
					res = tmp;
					break;
				}
			}
			if(!(r & 1)){
				auto tmp = get(r--, ranges);
				if(tmp.first != -1){
					res = tmp;
					break;
				}
			}
		}
		return res;
	}

	int querySum(int l, int r){
		int res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1){
				res += range[l].second - range[l].first + 1;
				++l;
			}
			if(!(r & 1)){
				res += range[r].second - range[r].first + 1;
				--r;
			}
		}
		return res;
	}
};

struct HeavyLight{
	int n;
	vector<vector<int>> adj;
	vector<int> parent, level, size, heavy, head, pos;
	int cur_pos;
	SegmentTree * st;

	HeavyLight(int n, SegmentTree * st): n(n), st(st){
		adj.resize(n);
		parent.resize(n);
		level.resize(n);
		size.resize(n);
		heavy.resize(n, -1);
		head.resize(n);
		pos.resize(n);
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
		for(int v : adj[u]){
			if(v != parent[u] && v != heavy[u])
				build(v, v);
		}
	}

	void init(){
		cur_pos = 0;
		dfs(0);
		build(0, 0);
	}

	int query(int a, int b){
		pair<int, int> res = {-1, 0};
		int dist = 0;
		vector<pair<int, int>> ranges;
		while(head[a] != head[b]){
			if(level[head[a]] > level[head[b]]) swap(a, b);
			ranges.emplace_back(pos[head[b]], pos[b]);
			dist += st->querySum(pos[head[b]], pos[b]);
			b = parent[head[b]];
		}
		if(level[a] > level[b]) swap(a, b);
		ranges.emplace_back(pos[a], pos[b]);
		dist += st->querySum(pos[a], pos[b]);
		for(const auto & par : ranges){
			auto tmp = st->query(par.first, par.second, ranges);
			if(tmp.first != -1){
				res = tmp;
				break;
			}
		}
		return 2*res.second > dist ? res.first : -1;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n;
	vector<int> arr(n);
	for(int & a : arr){
		cin >> a;
	}
	SegmentTree * st = new SegmentTree(n);
	HeavyLight hld(n, st);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		--u, --v;
		hld.adj[u].push_back(v);
		hld.adj[v].push_back(u);
	}
	hld.init();
	for(int i = 0; i < n; ++i){
		st->update(hld.pos[i], -1, arr[i]);
	}
	cin >> q;
	while(q--){
		int t, u, v;
		cin >> t >> u >> v;
		if(t == 1)
			cout << hld.query(u-1, v-1) << "\n";
		else
			hld.st->update(hld.pos[u-1], st->ST[hld.pos[u-1] + n], v);
	}

	return 0;
}