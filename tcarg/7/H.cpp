#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9+7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<vector<int>> pares(n);
		for(int i = 0; i < n; ++i){
			int ai;
			cin >> ai;
			pares[ai-1].push_back(i);
		}
		for(int i = 0; i < n; ++i){
			int ai;
			cin >> ai;
			pares[ai-1].push_back(i);
		}
		vector<vector<int>> adj(n);
		for(int i = 0; i < n; ++i){
			adj[pares[i][0]].push_back(pares[i][1]);
			adj[pares[i][1]].push_back(pares[i][0]);
		}
		int sz = 0;
		vector<bool> vis(n);
		function<void(int)> dfs = [&](int u){
			vis[u] = true;
			for(int v : adj[u]){
				if(!vis[v]) dfs(v);
			}
		};
		for(int u = 0; u < n; ++u){
			if(!vis[u]){
				dfs(u);
				sz++;
			}
		}
		cout << power(2, sz) << "\n";
	}
	return 0;
}