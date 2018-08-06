#include <bits/stdc++.h>
using namespace std;

int inf = 1 << 30;

bool bellmanFord(int start, int dest, vector<vector<int>> & graph, vector<int> & energy, vector<bool> & restricted){
	int V = graph.size();
	vector<int> costs(V, inf), processed(V), prev(V, -1);
	vector<bool> inQueue(V, false);
	queue<int> Q;
	costs[start] = 0;
	Q.push(start);
	while(!Q.empty()){
		int u = Q.front(); Q.pop(); inQueue[u] = false;
		++processed[u];
		if(processed[u] == V){
			int v = u;
			queue<int> Q2;
			vector<bool> visited(V, false);
			while(true){
				Q2.push(v);
				visited[v] = true;
				if(v == u)
					break;
				v = prev[v];
			}
			while(!Q2.empty()){
				int curr = Q2.front(); Q2.pop();
				restricted[curr] = true;
				for(int dest : graph[curr]){
					if(!visited[dest]){
						visited[dest] = true;
						Q2.push(dest);
					}
				}
			}
			if(restricted[dest])
				return true;
			else
				return bellmanFord(start, dest, graph, energy, restricted);
		}
		for(int v : graph[u]){
			if(restricted[v]) continue;
			int nuevo = costs[u] + energy[v];
			if(nuevo < 100 && nuevo < costs[v]){
				if(!inQueue[v]){
					Q.push(v);
					inQueue[v] = true;
				}
				costs[v] = nuevo;
				prev[v] = u;
			}
		}
	}
	return costs[dest] < 100;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int V, deg, v;
	while(cin >> V && V != -1){
		vector<vector<int>> graph(V, vector<int>());
		vector<int> energy(V);
		for(int u = 0; u < V; ++u){
			cin >> energy[u];
			energy[u] *= -1;
			cin >> deg;
			while(deg--){
				cin >> v;
				if(v - 1 < V)
					graph[u].push_back(v - 1);
			}
		}
		int start = 0, end = V - 1;
		vector<bool> restricted(V, false);
		if(bellmanFord(start, end, graph, energy, restricted))
			cout << "winnable\n";
		else
			cout << "hopeless\n";
	}
	return 0;
}