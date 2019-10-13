#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli inf = numeric_limits<lli>::max();

struct edge{
	int u, v; lli w; int id;
	bool operator<(const edge & e) const{
		return w < e.w;
	}
	bool operator>(const edge & e) const{
		return w > e.w;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<edge>> adj(n);
	for(int i = 0; i < m; ++i){
		int u, v; lli w;
		cin >> u >> v >> w;
		adj[u-1].push_back({u-1, v-1, w, i});
		adj[v-1].push_back({v-1, u-1, w, i});
	}
	int s, t;
	cin >> s >> t;
	--s, --t;

	priority_queue<edge, vector<edge>, greater<edge>> Q;
	vector<lli> dists(n, inf);
	vector<vector<pair<int, int>>> counter(n);
	dists[s] = 0;
	Q.push({-1, s, 0});
	while(!Q.empty()){
		int u = Q.top().v; Q.pop();
		if(u == t) break;
		for(edge & current : adj[u]){
			int v = current.v;
			lli nuevo = dists[u] + current.w;
			if(nuevo == dists[v]){
				counter[v].push_back({u, current.id});
			}else if(nuevo < dists[v]){
				dists[v] = nuevo;
				counter[v] = {{u, current.id}};
				Q.push({-1, v, nuevo});
			}
		}
	}

	int ans = 0;
	queue<int> q;
	q.push(t);
	vector<bool> vis(n);
	vector<bool> good(m);
	vis[t] = true;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto & curr : counter[u]){
			int v = curr.first;
			good[curr.second] = true;
			if(vis[v]) continue;
			q.push(v);
			vis[v] = true;
		}
	}
	for(int i = 0; i < m; ++i){
		ans += good[i];
	}

	cout << ans << "\n";
	return 0;
}