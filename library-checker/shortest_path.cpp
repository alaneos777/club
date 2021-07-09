#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli inf = 1e18;
using pii = pair<lli, int>;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	vector<vector<pii>> adj(n);
	for(int i = 0; i < m; ++i){
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
	}
	vector<int> parent(n, -1);
	priority_queue<pii, vector<pii>, greater<pii>> q;
	vector<lli> dist(n, inf);
	q.emplace(0, s);
	dist[s] = 0;
	bool found = false;
	while(!q.empty()){
		auto[dist_s_u, u] = q.top(); q.pop();
		if(u == t){
			found = true;
			break;
		}
		if(dist[u] < dist_s_u) continue;
		for(auto[v, dist_u_v] : adj[u]){
			lli dist_s_v = dist_s_u + dist_u_v;
			if(dist_s_v < dist[v]){
				dist[v] = dist_s_v;
				parent[v] = u;
				q.emplace(dist_s_v, v);
			}
		}
	}
	if(found){
		deque<int> path;
		for(int u = t; u != -1; u = parent[u]){
			path.push_front(u);
		}
		cout << dist[t] << " " << path.size()-1 << "\n";
		for(int i = 0; i+1 < path.size(); ++i){
			cout << path[i] << " " << path[i+1] << "\n";
		}
	}else{
		cout << "-1\n";
	}
	return 0;
}