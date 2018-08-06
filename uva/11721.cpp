#include <bits/stdc++.h>
using namespace std;

int inf = 1 << 30;

struct edge{
	int dest, cost;
};

vector<bool> bellmanFord(int start, vector<vector<edge>> & graph){
	int V = graph.size();
	vector<int> costs(V, inf), costs_before, processed(V), prev(V, -1);
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
			vector<bool> ans(V);
			for(int i = 0; i < V; ++i){
				//cout << costs_before[i] << " -> " << costs[i] << "\n";
				ans[i] = costs_before[i] == costs[i];
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
	vector<bool> ans(V, true);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int casos, V, E, u, v, t;
	cin >> casos;
	for(int caso = 1; caso <= casos; ++caso){
		cin >> V >> E;
		vector<vector<edge>> graph(V, vector<edge>());
		for(int i = 0; i < E; ++i){
			cin >> u >> v >> t;
			graph[u].push_back({v, t});
		}
		vector<bool> ans = bellmanFord(0, graph);
		cout << "Case " << caso << ": ";
		int count = 0;
		for(int i = 0; i < V; ++i){
			if(!ans[i]){
				++count;
				cout << i << " ";
			}
		}
		if(count == 0)
			cout << "impossible";
		cout << "\n";
	}
	return 0;
}