#include <bits/stdc++.h>
using namespace std;

struct edge{
	int dest, cost;
};

int inf = 1 << 30;

bool bellmanFord(int start, vector<vector<edge>> & graph){
	int V = graph.size();
	vector<int> costs(V, inf);
	costs[start] = 0;
	bool cambio = true;
	int j = 1;
	while(cambio){
		cambio = false;
		for(int u = 0; u < V; ++u){
			if(costs[u] == inf) continue;
			for(edge & current : graph[u]){
				int v = current.dest;
				int nuevo = costs[u] + current.cost;
				if(nuevo < costs[v]){
					if(j == V)
						return true;
					costs[v] = nuevo;
					cambio = true;
				}
			}
		}
		j++;
	}
	return false;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int c, V, E, u, v, w;
	cin >> c;
	while(c--){
		cin >> V >> E;
		vector<vector<edge>> graph(V, vector<edge>());
		for(int i = 0; i < E; ++i){
			cin >> u >> v >> w;
			graph[u].push_back({v, w});
		}
		if(bellmanFord(0, graph))
			cout << "possible\n";
		else
			cout << "not possible\n";
	}
	return 0;
}