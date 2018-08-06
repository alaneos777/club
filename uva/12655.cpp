#include <bits/stdc++.h>
using namespace std;
struct edge{
	int source, dest, cost;
	bool operator >(const edge & e) const{
		return cost > e.cost;
	}
};

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent;

	disjointSet(int N){
		this->N = N;
		parent.resize(N);
		rank.resize(N);
	}

	void makeSet(int v){
		parent[v] = v;
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a);
		b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
		}else{
			parent[b] = a;
			if(rank[a] == rank[b]){
				++rank[a];
			}
		}
	}
};

void dfs_tree(int prev, int u, vector<vector<edge>> & graph, vector<int> & parent, vector<int> & peso){
	for(edge & curr : graph[u]){
		int v = curr.dest, w = curr.cost;
		if(v == prev) continue;
		parent[v] = u;
		peso[v] = w;
		dfs_tree(u, v, graph, parent, peso);
	}
}

int dfs(int i, vector<int> & parent, vector<int> & level){
	if(i == 0) return 0;
	if(level[parent[i]] != -1) return level[i] = 1 + level[parent[i]];
	return level[i] = 1 + dfs(parent[i], parent, level);
}

void pre(vector<int> & level, vector<int> & parent, vector<int> & peso, vector<vector<int>> & maximo, vector<vector<int>> & DP, int n){
	for(int i = n - 1; i >= 0; --i){
		if(level[i] == -1){
			level[i] = dfs(i, parent, level);
		}
	}
	for(int u = 0; u < n; u++){
		DP[u][0] = parent[u];
		maximo[u][0] = peso[u];
	}
	for(int i = 1; (1 << i) <= n; ++i){
		for(int u = 0; u < n; ++u){
			DP[u][i] = DP[DP[u][i - 1]][i - 1];
			maximo[u][i] = min(maximo[u][i - 1], maximo[DP[u][i - 1]][i - 1]);
		}
	}
}

int lca(vector<int> & level, vector<vector<int>> & maximo, vector<vector<int>> & DP, int p, int q){
	if(level[p] < level[q]) swap(p, q);
	int lg;
	for(lg = 1; (1 << lg) <= level[p]; ++lg);
	lg--;
	int maxi = 1 << 30;
	for(int i = lg; i >= 0; --i){
		if(level[p] - (1 << i) >= level[q]){
			maxi = min(maxi, maximo[p][i]);
			p = DP[p][i];
		}
	}
	if(p == q) return maxi;
 
	for(int i = lg; i >= 0; --i){
		if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
			maxi = min(maxi, min(maximo[p][i], maximo[q][i]));
			p = DP[p][i];
			q = DP[q][i];
		}
	}
	maxi = min(maxi, min(maximo[p][0], maximo[q][0]));
	return maxi;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, s, a, b, w;
	while(cin >> n >> m >> s){
		vector<edge> edges(m);
		for(int i = 0; i < m; ++i){
			cin >> a >> b >> w;
			edges[i] = {a - 1, b - 1, w};
		}
		sort(edges.begin(), edges.end(), greater<edge>());
		vector<edge> MST;
		disjointSet DS(n);
		for(int u = 0; u < n; ++u)
			DS.makeSet(u);
		int i = 0;
		while(i < m && MST.size() < n - 1){
			edge current = edges[i++];
			int u = current.source, v = current.dest;
			if(DS.findSet(u) != DS.findSet(v)){
				MST.push_back(current);
				DS.unionSet(u, v);
			}
		}
		vector<vector<edge>> graph(n, vector<edge>());
		for(edge & current : MST){
			int u = current.source, v = current.dest, w = current.cost;
			graph[u].push_back({u, v, w});
			graph[v].push_back({v, u, w});
		}
		vector<int> parent(n), level(n, -1);
		vector<int> peso(n);
		vector<vector<int>> maximo(n, vector<int>(20, 1 << 30));
		vector<vector<int>> DP(n, vector<int>(20));
		level[0] = 0;
		peso[0] = 1 << 30;
		dfs_tree(-1, 0, graph, parent, peso);
		pre(level, parent, peso, maximo, DP, n);
		for(int i = 0; i < s; ++i){
			cin >> a >> b;
			--a, --b;
			cout << lca(level, maximo, DP, a, b) << "\n";
		}
	}
	return 0;
}