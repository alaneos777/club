#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli inf = 1e18;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> w(n), end(n), path;
	vector<bool> isend(2*n);
	vector<lli> sum(n);
	for(int & wi : w){
		cin >> wi;
	}
	vector<vector<int>> adj(n);
	for(int i = 0; i < n-1; ++i){
		int u, v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}

	int t = 0;

	function<void(int, int)> dfs = [&](int u, int p){
		sum[u] = w[u];
		t++;
		path.push_back(u);
		for(int v : adj[u]){
			if(v == p) continue;
			dfs(v, u);
			sum[u] += sum[v];
		}
		end[u] = t++;
		isend[end[u]] = true;
		path.push_back(u);
	};
	dfs(0, -1);

	vector<vector<lli>> mem(t+1, vector<lli>(k+1, -inf));
	vector<vector<bool>> calc(t+1, vector<bool>(k+1));

	function<lli(int, int)> f = [&](int pos, int rem){
		if(calc[pos][rem]) return mem[pos][rem];
		calc[pos][rem] = true;
		lli & ans = mem[pos][rem];
		if(pos == t){
			return ans = (rem == 0 ? 0 : -inf);
		}else if(isend[pos]){
			return ans = f(pos + 1, rem);
		}else if(rem == 0){
			return ans = 0;
		}
		return ans = max(sum[path[pos]] + f(end[path[pos]] + 1, rem-1), f(pos + 1, rem));
	};

	if(f(0, k) <= -inf/100){
		cout << "Impossible\n";
	}else{
		cout << f(0, k) << "\n";
	}

	return 0;
}