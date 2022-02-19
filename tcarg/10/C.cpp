#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (int i = 0; i < (n); i++)
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define f first
#define s second
#define rand(i, j) uniform_int_distribution<ll>((ll)(i), (ll)(j))(rng)
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef double ld;
typedef long double lld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.f << ", " << p.s << ")"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
	cout << "["; for (int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i]; } return cout << "]";
}
template<typename T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<typename T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }


//2 147 483 647 int max
//9 223 372 036 854 775 807 ll max
struct SCC {
	int n; 
	std::vector<std::vector<int>> g, rg, scc_graph, comps;
	std::vector<int> id, ord, roots, topo_ord;
	std::vector<bool> vis;

	void init(int n_) {
		n = n_;
		g.assign(n, std::vector<int>());
		rg.assign(n, std::vector<int>());
		scc_graph.assign(n, std::vector<int>());
		comps.assign(n, std::vector<int>());
		vis.assign(n, false);
		id.assign(n, -1);
		ord.clear();
		roots.clear();     
		topo_ord.clear();  
	}

	void ae(int u, int v) {
		g[u].push_back(v);
		rg[v].push_back(u);
	}

	void dfs_order(int u) {
		vis[u] = true;
		for (auto &v : g[u]) {
			if (vis[v]) 
				continue;
			dfs_order(v);
		}
		ord.push_back(u);
	}

	void dfs_color(int u, int c) {
		id[u] = c;
		for (int &v : rg[u]) 
			if (id[v] == -1) 
				dfs_color(v, c);
	}

	void topological_sort() {
		std::vector<int> in(n);
		std::list<int> todo;
		for (int i = 0; i < n; ++i) 
			for (auto &j : scc_graph[i])
				++in[j];
		for (int i = 0; i < n; ++i)
			if (!in[i] && id[i] == i)
				todo.push_back(i);
		while (!todo.empty()) {
			int u = todo.front();
			todo.pop_front();
			topo_ord.push_back(u);
			for (auto &v : scc_graph[u]) 
				if (!(--in[v])) 
					todo.push_back(v);
		}
	}

	void build_scc_graph() {
		for (int i = 0; i < n; ++i) {
			comps[id[i]].push_back(i);
			for (auto &j : g[i]) {
				if (id[i] == id[j]) 
					continue;
				scc_graph[id[i]].push_back(id[j]);
			}
		}
		topological_sort();
	}

	void gen() {
		for (int i = 0; i < n; ++i) {
			if (!vis[i])
				dfs_order(i);
		}
		reverse(ord.begin(), ord.end());
		for (auto &x : ord) 
			if (id[x] == -1) 
				dfs_color(x, x), roots.push_back(x);
	}
};



int main(){
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;
	SCC g;
	g.init(n);

	vector<vector<int>> adj(n), cadj(n);
	vector<pii> ed;
	forn(i, m){
		int a, b;
		cin >> a >> b;
		a--; b--;
		g.ae(a, b);
		ed.emplace_back(a, b);
	}

	g.gen();
	g.build_scc_graph();

	forn(i, m){
		if(g.id[ed[i].f] == g.id[ed[i].s]){
			cadj[ed[i].f].pb(ed[i].s);
		} else {
			adj[ed[i].f].pb(ed[i].s);
		}
	}

	// cout << cadj << " " << adj << "\n";


	vector<int> dp(n);
	vector<bool> used(n);
	int ans = 0;
	for(int c: g.topo_ord){
		for(int x: g.comps[c]){
			map<int, int> l;
			function<void(int, int)> dfs = [&](int u, int len){
				ckmax(l[u], len);
				used[u] = true;
				for(int oth: cadj[u]){
					if(!used[oth]) dfs(oth, len+1);
				}
				used[u] = false;
			};
			dfs(x, 1);
			for(int y: g.comps[c]){
				for(int z: adj[y]) ckmax(dp[z], (int) (dp[x] + l[y]));
				ckmax(ans, (int) (dp[x] + l[y]));
			}
		}
		// cout << g.comps[c] << " " << dp << "\n";
	}
	forn(i, n){
		ckmax(ans, (int) (dp[i] + g.comps[g.id[i]].size()));
	}
	cout << ans << "\n";
	
}