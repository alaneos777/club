#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli inf = numeric_limits<lli>::max();

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent, count;

	disjointSet(int N): N(N), parent(N), rank(N){}

	void makeSet(int v){
		parent[v] = v;
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a), b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
		}else{
			parent[b] = a;
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};

struct edge{
	int u, v; lli w;
	bool operator<(const edge & e) const{
		return w < e.w;
	}
};

struct tree{
	vector<int> parent, level;
	vector<lli> weight;
	vector<vector<lli>> dists;
	vector<vector<int>> DP;
	int n, root;

	void dfs(int u, const vector<vector<edge>> & adj){
		for(const edge & curr : adj[u]){
			int v = curr.v;
			lli w = curr.w;
			if(v != parent[u]){
				parent[v] = u;
				weight[v] = w;
				level[v] = level[u] + 1;
				dfs(v, adj);
			}
		}
	}

	tree(const vector<vector<edge>> & adj, int root): n(adj.size()), root(root), parent(adj.size()), level(adj.size()), weight(adj.size()), dists(adj.size(), vector<lli>(22)), DP(adj.size(), vector<int>(22)){
		parent[root] = root;
		dfs(root, adj);
		pre();
	}

	void pre(){
		for(int u = 0; u < n; u++){
			DP[u][0] = parent[u];
			dists[u][0] = weight[u];
		}
		for(int i = 1; (1 << i) <= n; ++i){
			for(int u = 0; u < n; ++u){
				DP[u][i] = DP[DP[u][i - 1]][i - 1];
				dists[u][i] = max(dists[u][i - 1], dists[DP[u][i - 1]][i - 1]);
			}
		}
	}

	lli maximum(int p, int q){
		if(level[p] < level[q]) swap(p, q);
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		lli ans = 0;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= level[q]){
				ans = max(ans, dists[p][i]);
				p = DP[p][i];
			}
		}
		if(p == q) return ans;
	 
		for(int i = lg; i >= 0; --i){
			if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
				ans = max({ans, dists[p][i], dists[q][i]});
				p = DP[p][i];
				q = DP[q][i];
			}
		}
		ans = max({ans, dists[p][0], dists[q][0]});
		return ans;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<edge> edges(m);
	for(int i = 0; i < m; ++i){
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
		edges[i].u--;
		edges[i].v--;
	}
	disjointSet DS(n);
	for(int i = 0; i < n; ++i){
		DS.makeSet(i);
	}
	sort(edges.begin(), edges.end());

	lli cost_mst = 0;
	int i = 0, cnt = 0;
	vector<bool> edgeUsed(m);
	vector<vector<edge>> adj(n);
	while(cnt < n-1 && i < edges.size()){
		auto & curr = edges[i];
		if(DS.findSet(curr.u) != DS.findSet(curr.v)){
			DS.unionSet(curr.u, curr.v);
			adj[curr.u].push_back({curr.u, curr.v, curr.w});
			adj[curr.v].push_back({curr.v, curr.u, curr.w});
			edgeUsed[i] = true;
			cost_mst += curr.w;
			cnt++;
		}
		i++;
	}

	tree mst(adj, 0);
	lli cost_2nd_mst = inf;
	for(int i = 0; i < edges.size(); ++i){
		if(edgeUsed[i]) continue;
		cost_2nd_mst = min(cost_mst - mst.maximum(edges[i].u, edges[i].v) + edges[i].w, cost_2nd_mst);
	}

	cout << cost_mst << " ";
	if(cost_2nd_mst != inf){
		cout << cost_2nd_mst << "\n";
	}else{
		cout << -1 << "\n";
	}
	return 0;
}