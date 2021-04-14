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
	int l, r, c, time, index, p;
	query() {}
	query(int l, int r, int c, int time, int index, int p = -1): l(l), r(r), c(c), time(time), index(index), p(p) {}
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

auto muSieve(int n){
	vector<int> primes, lp(n+1), mu(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const int M = 5000;
const auto mu = muSieve(M);

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		if(mu[i]){
			for(int j = i; j <= n; j += i){
				divs[j].push_back(i);
			}
		}
	}
	return divs;
}

const auto divs = divsSieve(M);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> vals(n), prev_vals;
	for(int& ci : vals) cin >> ci;
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

	prev_vals = vals;
	vector<query> queries;
	vector<update> updates;
	for(int i = 0; i < m; ++i){
		int type, u, v;
		cin >> type >> u >> v;
		if(type == 1){
			--u, --v;
			int c;
			cin >> c;
			if(start[u] > start[v]) swap(u, v);
			int p = hld.lca(u, v);
			if(p == u){
				queries.emplace_back(start[u], start[v], c, updates.size(), queries.size());
			}else{
				queries.emplace_back(end[u], start[v], c, updates.size(), queries.size(), p);
			}
		}else{
			--u;
			updates.emplace_back(prev_vals[u], v, u);
			prev_vals[u] = v;
		}
	}

	S = 2*powl(n, 2.0l/3.0l);
	sort(queries.begin(), queries.end());
	vector<int> answers(queries.size());
	vector<int> freq_idx(n), freq_d(M+1);
	int prevL = 0, prevR = -1, updatesCnt = 0;

	auto remove = [&](int u){
		int& f1 = freq_idx[u];
		f1--;
		for(int d : divs[vals[u]]){
			if(f1 == 1) freq_d[d]++;
			else if(f1 == 0) freq_d[d]--;
		}
	};

	auto add = [&](int u){
		int& f1 = freq_idx[u];
		f1++;
		for(int d : divs[vals[u]]){
			if(f1 == 2) freq_d[d]--;
			else if(f1 == 1) freq_d[d]++;
		}
	};

	auto change = [&](int u, int next){
		if(freq_idx[u] == 1){
			remove(u);
			vals[u] = next;
			add(u);
		}
		vals[u] = next;
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

		int ans = 0;
		for(int d : divs[q.c]){
			if(mu[d] == 1) ans += freq_d[d];
			else if(mu[d] == -1) ans -= freq_d[d];
		}
		if(q.p != -1 && __gcd(vals[q.p], q.c) == 1){
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