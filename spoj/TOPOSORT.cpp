#include <bits/stdc++.h>
using namespace std;

vector<int> topological_sort(vector<vector<int>> & graph){
	vector<int> order;
	int V = graph.size();
	int visited = 0;
	vector<int> indegree(V);
	for(auto & node : graph){
		for(int & dest : node){
			++indegree[dest];
		}
	}
	priority_queue<int, vector<int>, greater<int>> Q;
	for(int i = 0; i < V; ++i){
		if(indegree[i] == 0) Q.push(i);
	}
	while(!Q.empty()){
		int source = Q.top();
		Q.pop();
		order.push_back(source);
		++visited;
		for(int & dest : graph[source]){
			--indegree[dest];
			if(indegree[dest] == 0) Q.push(dest);
		}
	}
	if(visited == V) return order;
	else return {};
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, u, v;
	cin >> n >> m;
	vector<vector<int>> graph(n, vector<int>());
	vector<bool> visited(n, false);
	for(int i = 0; i < m; i++){
		cin >> u >> v;
		graph[u - 1].push_back(v - 1);
	}
	vector<int> ans = topological_sort(graph);
	if(ans.size()){
		for(int & x : ans){
			cout << x + 1 << " ";
		}
	}else{
		cout << "Sandro fails.";
	}
	return 0;
}