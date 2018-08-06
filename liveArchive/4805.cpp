#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int dfs(int i, vector<int> & parent, vector<int> & level){
	if(i == 0) return 0;
	if(level[parent[i]] != -1) return level[i] = 1 + level[parent[i]];
	return level[i] = 1 + dfs(parent[i], parent, level);
}

void pre(vector<int> & level, vector<int> & parent, vector<lli> & peso, vector<vector<lli>> & maximo, vector<vector<lli>> & DP, int n){
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
			maximo[u][i] = maximo[u][i - 1] + maximo[DP[u][i - 1]][i - 1];
		}
	}
}

lli lca(vector<int> & level, vector<vector<lli>> & maximo, vector<vector<lli>> & DP, int p, int q){
	if(level[p] < level[q]) swap(p, q);
	int lg;
	for(lg = 1; (1 << lg) <= level[p]; ++lg);
	lg--;
	lli maxi = 0;
	for(int i = lg; i >= 0; --i){
		if(level[p] - (1 << i) >= level[q]){
			maxi = maxi + maximo[p][i];
			p = DP[p][i];
		}
	}
	if(p == q) return maxi;
 
	for(int i = lg; i >= 0; --i){
		if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
			maxi = maximo[p][i] + maximo[q][i] + maxi;
			p = DP[p][i];
			q = DP[q][i];
		}
	}
	maxi = maximo[p][0] + maximo[q][0] + maxi;
	return maxi;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, q, s, t;
	while(cin >> n && n){
		vector<int> parent(n), level(n, -1);
		vector<lli> peso(n);
		vector<vector<lli>> maximo(n, vector<lli>(20));
		vector<vector<lli>> DP(n, vector<lli>(20));
		level[0] = 0;
		for(int i = 1; i < n; ++i){
			cin >> parent[i] >> peso[i];
		}
		pre(level, parent, peso, maximo, DP, n);
		cin >> q;
		for(int i = 0; i < q; ++i){
			cin >> s >> t;
			if(i) cout << " ";
			cout << lca(level, maximo, DP, s, t);
		}
		cout << "\n";
	}
	return 0;
}