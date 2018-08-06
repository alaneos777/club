#include <bits/stdc++.h>
using namespace std;

int dfs(int i, vector<int> & parent, vector<int> & level){
	if(i == 0) return 0;
	if(level[parent[i]] != -1) return level[i] = 1 + level[parent[i]];
	return level[i] = 1 + dfs(parent[i], parent, level);
}

void pre(vector<int> & level, vector<int> & parent, vector<vector<int>> & DP, int n){
	for(int i = n - 1; i >= 0; --i){
		if(level[i] == -1){
			level[i] = dfs(i, parent, level);
		}
	}
	for(int u = 0; u < n; u++){
		DP[u][0] = parent[u];
	}
	for(int i = 1; (1 << i) <= n; ++i){
		for(int u = 0; u < n; ++u){
			DP[u][i] = DP[DP[u][i - 1]][i - 1];
		}
	}
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

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, u, v, c, q;
	cin >> n;
	vector<int> parent(n), level(n, -1);
	vector<vector<int>> DP(n, vector<int>(20));
	level[0] = 0;
	for(int i = 0; i < n; ++i){
		cin >> c;
		for(int j = 0; j < c; ++j){
			cin >> v;
			parent[v] = i;
		}
	}
	pre(level, parent, DP, n);
	cin >> q;
	for(int i = 0; i < q; ++i){
		cin >> u >> v;
		cout << lca(level, parent, DP, u, v) << "\n";
	}
	return 0;
}