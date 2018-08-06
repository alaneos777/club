#include <bits/stdc++.h>
using namespace std;

struct edge{
	int dest, cost;
};

int inf = 1 << 30;

vector<int> bellmanFord(int start, vector<vector<edge>> & graph){
	int V = graph.size();
	vector<int> costs(V, inf), costs_before, processed(V);
	vector<bool> inQueue(V, false);
	queue<int> Q;
	costs[start] = 0;
	Q.push(start);
	while(!Q.empty()){
		int u = Q.front(); Q.pop(); inQueue[u] = false;
		++processed[u];
		if(processed[u] == V){
			costs_before = costs;
		}else if(processed[u] == 2*V){
			vector<int> ans(V);
			for(int i = 0; i < V; ++i){
				if(costs_before[i] != costs[i])
					ans[i] = -1;
				else
					ans[i] = costs[i];
			}
			return ans;
		}
		for(edge & current : graph[u]){
			int v = current.dest;
			int nuevo = costs[u] + current.cost;
			if(nuevo < costs[v]){
				if(!inQueue[v]){
					Q.push(v);
					inQueue[v] = true;
				}
				costs[v] = nuevo;
			}
		}
	}
	return costs;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int V, E, u, v, q;
	int caso = 1;
	while(cin >> V){
		cout << "Set #" << caso++ << "\n";
		vector<int> busyness(V);
		vector<vector<edge>> graph(V, vector<edge>());
		for(int i = 0; i < V; ++i)
			cin >> busyness[i];
		cin >> E;
		for(int i = 0; i < E; ++i){
			cin >> u >> v;
			int cost = busyness[v - 1] - busyness[u - 1]; cost = cost * cost * cost;
			graph[u - 1].push_back({v - 1, cost});
		}
		vector<int> costs(V, 0);
		if(V)
			costs = bellmanFord(0, graph);
		cin >> q;
		for(int i = 0; i < q; ++i){
			cin >> u;
			bool cycle;
			int cost = costs[u - 1];
			if(cost < 3 || cost == inf)
				cout << "?\n";
			else
				cout << cost << "\n";
		}
	}
	return 0;
}