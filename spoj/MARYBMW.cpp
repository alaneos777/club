#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

using edge = tuple<lli, int, int>;
const lli inf = 9e18;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		vector<edge> edges;
		for(int i = 0; i < m; ++i){
			int u, v;
			lli w;
			cin >> u >> v >> w;
			edges.emplace_back(w, u-1, v-1);
		}
		sort(edges.begin(), edges.end(), greater<edge>());
		disjointSet ds(n);
		for(int i = 0; i < n; ++i){
			ds.makeSet(i);
		}
		vector<vector<pair<int, lli>>> tree(n);
		int sz = 0;
		for(int i = 0; i < edges.size() && sz < n-1; ++i){
			int u, v;
			lli w;
			tie(w, u, v) = edges[i];
			if(ds.findSet(u) != ds.findSet(v)){
				tree[u].emplace_back(v, w);
				tree[v].emplace_back(u, w);
				ds.unionSet(u, v);
				sz++;
			}
		}
		vector<lli> dist(n, inf);
		vector<bool> vis(n);
		vis[0] = true;
		queue<int> Q({0});
		while(!Q.empty()){
			int u = Q.front(); Q.pop();
			if(u == n-1) break;
			for(const auto& ed : tree[u]){
				int v; lli w;
				tie(v, w) = ed;
				if(!vis[v]){
					vis[v] = true;
					dist[v] = min(dist[u], w);
					Q.push(v);
				}
			}
		}
		if(!vis[n-1]) dist[n-1] = -1;
		cout << dist[n-1] << "\n";
	}
	return 0;
}