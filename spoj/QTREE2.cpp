#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct edge{
	int dest;
	lli cost;
};

void dfs_tree(int prev, int u, vector<vector<edge>> & graph, vector<int> & parent, vector<lli> & peso){
	for(edge & curr : graph[u]){
		int v = curr.dest;
		lli w = curr.cost;
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

void pre(vector<int> & level, vector<int> & parent, vector<lli> & peso, vector<vector<lli>> & suma, vector<vector<int>> & DP, int n){
	for(int i = n - 1; i >= 0; --i){
		if(level[i] == -1){
			level[i] = dfs(i, parent, level);
		}
	}
	for(int u = 0; u < n; u++){
		DP[u][0] = parent[u];
		suma[u][0] = peso[u];
	}
	for(int i = 1; (1 << i) <= n; ++i){
		for(int u = 0; u < n; ++u){
			DP[u][i] = DP[DP[u][i - 1]][i - 1];
			suma[u][i] = suma[u][i - 1] + suma[DP[u][i - 1]][i - 1];
		}
	}
}

lli dist(vector<int> & level, vector<vector<lli>> & suma, vector<vector<int>> & DP, int p, int q){
	if(level[p] < level[q]) swap(p, q);
	int lg;
	for(lg = 1; (1 << lg) <= level[p]; ++lg);
	lg--;
	lli sum = 0;
	for(int i = lg; i >= 0; --i){
		if(level[p] - (1 << i) >= level[q]){
			sum += suma[p][i];
			p = DP[p][i];
		}
	}
	if(p == q) return sum;
 
	for(int i = lg; i >= 0; --i){
		if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
			sum += suma[p][i] + suma[q][i];
			p = DP[p][i];
			q = DP[q][i];
		}
	}
	sum += suma[p][0] + suma[q][0];
	return sum;
}

int lca(vector<int> & level, vector<int> & parent, vector<vector<int>> & DP, int p, int q){
	if(level[p] < level[q]) swap(p, q);
	int lg;
	for(lg = 1; (1 << lg) <= level[p]; ++lg);
	lg--;
	for(int i = lg; i >= 0; --i){
		if(level[p] - (1 << i) >= level[q]){
			p = DP[p][i];
		}
	}
	if(p == q) return p;
 
	for(int i = lg; i >= 0; --i){
		if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
			p = DP[p][i];
			q = DP[q][i];
		}
	}
	return parent[p];
}

int ancestor(vector<int> & level, vector<vector<int>> & DP, int p, int k){
	int h = level[p] - k;
	if(h < 0) return -1;
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

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t, n, u, v, k;
	lli w;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		cin >> n;
		vector<vector<edge>> graph(n, vector<edge>());
		vector<int> parent(n), level(n, -1);
		vector<lli> peso(n);
		vector<vector<lli>> suma(n, vector<lli>(20));
		vector<vector<int>> DP(n, vector<int>(20));
		level[0] = 0;
		for(int i = 1; i < n; ++i){
			cin >> u >> v >> w;
			--u, --v;
			graph[u].push_back({v, w});
			graph[v].push_back({u, w});
		}
		dfs_tree(-1, 0, graph, parent, peso);
		pre(level, parent, peso, suma, DP, n);
		string q;
		while(cin >> q && q != "DONE"){
			if(q == "DIST"){
				cin >> u >> v;
				--u, --v;
				cout << dist(level, suma, DP, u, v) << "\n";
			}else{
				cin >> u >> v >> k;
				--u, --v;
				int l = lca(level, parent, DP, u, v);
				if(k <= level[u] - level[l] + 1){
					cout << ancestor(level, DP, u, k - 1)+1 << "\n";
				}else{
					k = level[u] + level[v] - 2 * level[l] + 1 - k;
					cout << ancestor(level, DP, v, k)+1 << "\n";
				}
			}
		}
		cout << "\n";
	}
	return 0;
}