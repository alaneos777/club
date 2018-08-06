#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> edge;

int inf = 1 << 30;

int dijkstra(vector<vector<int>> & graph, vector<bool> & hasAirport, int start, int end){
	int V = graph.size();
	priority_queue<edge, vector<edge>, greater<edge>> cola;
	vector<int> costs(V, inf);
	vector<bool> relaxed(V, false);
	cola.push(make_pair(!hasAirport[start], start));
	costs[start] = !hasAirport[start];
	relaxed[start] = true;
	while(!cola.empty()){
		int u = cola.top().second; cola.pop();
		if(end == u)
			return costs[u];
		relaxed[u] = true;
		for(int & v : graph[u]){
			if(relaxed[v]) continue;
			int nuevo = costs[u];
			if(!hasAirport[v]){
				++nuevo;
			}
			if(nuevo < costs[v]){
				cola.push(make_pair(nuevo, v));
				costs[v] = nuevo;
			}
		}
	}
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int cases;
	cin >> cases;
	for(int caso = 1; caso <= cases; ++caso){
		int n, m, k, u, v, q;
		cin >> n >> m >> k;
		vector<bool> hasAirport(n);
		for(int i = 0; i < k; ++i){
			cin >> u;
			hasAirport[u - 1] = true;
		}
		vector<vector<int>> graph(n, vector<int>());
		for(int i = 0; i < m; ++i){
			cin >> u >> v;
			graph[u - 1].push_back(v - 1);
			graph[v - 1].push_back(u - 1);
		}
		cin >> q;
		cout << "Case " << caso << ":\n";
		while(q--){
			cin >> u >> v;
			if(u == v)
				cout << "0\n";
			else
				cout << dijkstra(graph, hasAirport, u - 1, v - 1) << "\n";
		}
		cout << "\n";
	}
	return 0;
}