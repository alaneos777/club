#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1001001011;
const int M = 20;

int main(){
	int sz = 1 << M;
	set<pair<int, int>> st;
	for(int n = 0; n < sz; ++n){
		int out = n >> 1;
		out |= ((n & 1) & (((n >> 1) & 1) ^ ((n >> 2) & 1))) << (M - 1);
		st.emplace(min(n, out), max(n, out));
	}

	vector<vector<int>> adj(sz);
	for(auto par : st){
		int u, v;
		tie(u, v) = par;
		if(!(u == 0 && v == 0)){
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
	}

	vector<int> color(sz);
	function<bool(int, int, int&)> hasCycle = [&](int u, int p, int & tam){
		color[u] = 1;
		tam++;
		bool ans = false;
		for(int v : adj[u]){
			if(color[v] == 0){
				ans |= hasCycle(v, u, tam);
			}else if(color[v] == 1 && v != p){
				ans = true;
			}
		}
		color[u] = 2;
		return ans;
	};

	vector<bool> vis(sz);
	function<void(int)> dfs2 = [&](int u){
		vis[u] = 1;
		for(int v : adj[u]){
			if(!vis[v]){
				dfs2(v);
			}
		}
	};

	vector<vector<lli>> mem(2, vector<lli>(sz, -1));
	function<lli(int, bool, int)> dp = [&](int u, bool flag, int p){
		if(mem[flag][u] != -1) return mem[flag][u];
		lli ans = 1;
		for(int v : adj[u]){
			lli tmp = 0;
			if(v == p || v == 0) continue;
			tmp += dp(v, 0, u);
			if(flag == 0){
				tmp += dp(v, 1, u);
			}
			ans *= tmp;
			ans %= mod;
		}
		return mem[flag][u] = ans;
	};

	lli ans = 1;
	for(int u = 0; u < sz; ++u){
		if(color[u]) continue;
		int tam = 0;
		if(hasCycle(u, -1, tam)){
			vis = vector<bool>(sz);
			dfs2(u);
			vector<int> mapeo(sz), lista;
			for(int i = 0, id = 0; i < sz; ++i){
				if(vis[i]){
					mapeo[i] = id++;
					lista.push_back(i);
				}
			}
			int cnt = 0;
			for(int mask = 0; mask < (1 << tam); ++mask){
				bool test = true;
				for(int source : lista){
					if(!test) break;
					for(int dest : adj[source]){
						int b0 = ((mask >> mapeo[source]) & 1);
						int b1 = ((mask >> mapeo[dest]) & 1);
						test &= !(b0 == 1 && b1 == 1);
						if(!test) break;
					}
				}
				cnt += test;
			}
			ans *= cnt;
		}else{
			int start = u;
			if(start == 0) start++;
			ans *= dp(start, 0, -1) + dp(start, 1, -1);
		}
		ans %= mod;
	}
	
	cout << ans << "\n";
	return 0;
}