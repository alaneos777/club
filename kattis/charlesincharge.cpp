#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct edge{
	int dest;
	lli cost;
	edge(): dest(0), cost(0){}
	edge(int dest, lli cost): dest(dest), cost(cost){}
	bool operator>(const edge & b) const{
		return cost > b.cost;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int V, E, u, v;
	lli X, t;
	cin >> V >> E >> X;
	vector<vector<edge>> graph(V);
	for(int i = 0; i < E; ++i){
		cin >> u >> v >> t;
		--u, --v;
		graph[u].emplace_back(v, t);
		graph[v].emplace_back(u, t);
	}

	auto dijkstra = [&](int start, int dest, lli limit){
		priority_queue<edge, vector<edge>, greater<edge>> cola;
		vector<lli> costs(V, numeric_limits<lli>::max());
		vector<bool> relaxed(V);
		cola.push(edge(start, 0));
		costs[start] = 0;
		while(!cola.empty()){
			int u = cola.top().dest; cola.pop();
			if(u == dest) return costs[u];
			relaxed[u] = true;
			for(edge & current : graph[u]){
				int v = current.dest;
				if(current.cost > limit) continue;
				if(relaxed[v]) continue;
				lli nuevo = costs[u] + current.cost;
				if(nuevo < costs[v]){
					cola.push(edge(v, nuevo));
					costs[v] = nuevo;
				}
			}
		}
		return numeric_limits<lli>::max();
	};

	lli shortest_len = dijkstra(0, V - 1, numeric_limits<lli>::max()) * (100 + X) / 100;
	
	lli l = 0, r = 1e9 + 10, m = 0;
	while(true){
		m = l + (r - l) / 2;
		if(dijkstra(0, V - 1, m) <= shortest_len){
			if(dijkstra(0, V - 1, m - 1) > shortest_len){
				break;
			}else{
				r = m - 1;
			}
		}else{
			l = m + 1;
		}
	}

	cout << m << "\n";

	return 0;
}