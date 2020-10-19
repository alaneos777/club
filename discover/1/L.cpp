#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

using edge = pair<lli, int>;
const lli inf = 1e18;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<edge>> adj(n);
	while(m--){
		int u, v, l;
		cin >> u >> v >> l;
		adj[u-1].emplace_back(l, v-1);
	}
	vector<int> vis(n);
	priority_queue<edge, vector<edge>, greater<edge>> q;
	vector<lli> dist(n, inf);
	vis[0] = true;
	q.emplace(0, 0);
	dist[0] = 0;
	while(!q.empty()){
		lli dist_0u = q.top().first;
		int u = q.top().second;
		q.pop();
		if(dist[u] < dist_0u) continue;
		for(const edge & e : adj[u]){
			int v; lli dist_uv;
			tie(dist_uv, v) = e;
			if(dist_0u + dist_uv < dist[v]){
				dist[v] = dist_0u + dist_uv;
				vis[v] = true;
				q.emplace(dist_0u + dist_uv, v);
			}
		}
	}
	if(dist[n-1] == inf){
		cout << "Infinity\n";
	}else{
		cout << dist[n-1] << "\n";
	}
	return 0;
}