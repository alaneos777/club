#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> edge;

bool isBipartite(vector<vector<edge>> & graph, int k){
	int V = graph.size();
	vector<int> side(V, -1);
	queue<int> q;
	for (int st = 0; st < V; ++st) {
		if(side[st] != -1) continue;
		q.push(st);
		side[st] = 0;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (edge & current : graph[u]) {
				int v = current.first;
				if(current.second > k) continue;
				if (side[v] == -1) {
					side[v] = side[u] ^ 1;
					q.push(v);
				} else {
					if(side[v] == side[u]) return false;
				}
			}
		}
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int V, E, u, v;
	cin >> V >> E;
	vector<vector<edge>> graph(V, vector<edge>());
	for(int i = 1; i <= E; ++i){
		cin >> u >> v;
		--u, --v;
		graph[u].push_back({v, i});
		graph[v].push_back({u, i});
	}
	int l = 0, r = E, m;
	while(r - l > 1){
		m = (l + r) >> 1;
		if(isBipartite(graph, m)) l = m;
		else r = m;
	}
	cout << r;
	return 0;
}