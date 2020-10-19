#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, x, l;
	cin >> n >> m >> x >> l;
	--x, --l;
	vector<set<int>> adj(n);
	vector<int> cnt(n);
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		adj[u-1].insert(v-1);
		adj[v-1].insert(u-1);
		++cnt[u-1];
		++cnt[v-1];
	}
	queue<int> q;
	q.push(l);
	while(!q.empty()){
		int u = q.front(); q.pop();
		cnt[u] = 0;
		for(int v : adj[u]){
			adj[v].erase(u);
			if(cnt[v] - (int)adj[v].size() >= (cnt[v] + 1) / 2){
				q.push(v);
			}
		}
	}
	if(cnt[x] == 0){
		cout << "leave\n";
	}else{
		cout << "stay\n";
	}
	return 0;
}