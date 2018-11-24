#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli inf = numeric_limits<lli>::max();

struct edge{
	int dest;
	lli dist, cost;
	edge(): dest(0), dist(0), cost(0) {}
	edge(int dest, lli dist, lli cost): dest(dest), dist(dist), cost(cost){}
	bool operator>(const edge & e) const{
		if(dist != e.dist) return dist > e.dist;
		return cost > e.cost;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<edge>> graph(n);
	for(int i = 0; i < m; ++i){
		int u, v;
		lli dist, cost;
		cin >> u >> v >> dist >> cost;
		--u, --v;
		graph[u].emplace_back(v, dist, cost);
		graph[v].emplace_back(u, dist, cost);
	}

	vector<lli> dists(n, inf);
	vector<edge> allowed(n);
	dists[0] = 0;
	priority_queue<edge, vector<edge>, greater<edge>> Q;
	Q.emplace(0, 0, 0);

	while(!Q.empty()){
		int u = Q.top().dest; Q.pop();
		for(edge & current : graph[u]){
			int v = current.dest;
			lli nuevo = dists[u] + current.dist;
			if(nuevo == dists[v] && current.cost < allowed[v].cost){
				allowed[v] = current;
			}else if(nuevo < dists[v]){
				dists[v] = nuevo;
				allowed[v] = current;
				Q.emplace(v, nuevo, current.cost);
			}
		}
	}

	lli ans = 0;
	for(edge & current : allowed){
		ans += current.cost;
	}
	cout << ans << "\n";
	return 0;
}