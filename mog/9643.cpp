#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, l, k, mi;
	cin >> n >> l;
	vector<vector<int>> adj(n+1);
	vector<int> mem(n+1, -1);
	vector<bool> vis(n+1);
	for(int i = 1; i <= l; ++i){
		cin >> k;
		while(k--){
			cin >> mi;
			adj[i].push_back(mi);
		}
	}
	function<int(int)> f = [&](int u){
		vis[u] = true;
		if(mem[u] != -1) return mem[u];
		if(l + 1 <= u) return mem[u] = 1;
		int ans = 0;
		for(int v : adj[u]){
			ans += f(v);
			if(ans >= mod) ans -= mod;
		}
		return mem[u] = ans;
	};
	int b = f(1);
	int a = 0;
	for(int i = l + 1; i <= n; ++i){
		if(vis[i])
			a += f(i);
	}
	cout << b << " " << a << "\n";
	return 0;
}