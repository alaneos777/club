#include <bits/stdc++.h>
using namespace std;

int topologicalSort(vector<int> *graph, vector<int> & component, int *indegree){
	int visited = 0;
	queue<int> Q;
	for(auto & u : component){
		if(indegree[u] == 0) Q.push(u);
	}
	while(!Q.empty()){
		int source = Q.front();
		Q.pop();
		++visited;
		for(int & v : graph[source]){
			--indegree[v];
			if(indegree[v] == 0) Q.push(v);
		}
	}
	if(visited == component.size()) return component.size() - 1;
	else return component.size();
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int V, E;
	cin >> V >> E;
	vector<int> *graph = new vector<int>[V]();
	vector<int> *graph2 = new vector<int>[V]();
	int u, v;
	for(int i = 0; i < E; ++i){
		cin >> u >> v;
		--u, --v;
		graph[u].push_back(v);
		graph2[u].push_back(v);
		graph2[v].push_back(u);
	}
	int ans = 0;
	bool *visited = new bool[V]();
	int *indegree = new int[V]();
	for(int u = 0; u < V; ++u){
		for(int & v : graph[u]){
			++indegree[v];
		}
	}
	for(int i = 0; i < V; ++i){
		if(visited[i]) continue;
		vector<int> component;
		queue<int> Q;
		Q.push(i);
		visited[i] = true;
		while(!Q.empty()){
			int u = Q.front(); Q.pop();
			component.push_back(u);
			for(int & v : graph2[u]){
				if(visited[v]) continue;
				Q.push(v);
				visited[v] = true;
			}
		}
		ans += topologicalSort(graph, component, indegree);
	}
	cout << ans << "\n";
	return 0;
}