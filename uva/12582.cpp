#include <bits/stdc++.h>
using namespace std;

string path;

void dfs(vector<vector<int>> & graph, vector<bool> & visited, int pos){
	int source = path[pos] - 'A';
	visited[source] = true;
	for(int i = pos + 1; i < path.size(); i++){
		int dest = path[i] - 'A';
		if(dest == source) break;
		if(!visited[dest]){
			dfs(graph, visited, i);
			graph[source].push_back(dest);
			graph[dest].push_back(source);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; caso++){
		cin >> path;
		vector<vector<int>> graph(26, vector<int>());
		vector<bool> visited(26, false);
		dfs(graph, visited, 0);
		cout << "Case " << caso << "\n";
		for(int i = 0; i < 26; i++){
			if(graph[i].size() > 0){
				char c = i + 'A';
				cout << c << " = " << graph[i].size() << "\n";
			}
		}
	}
	return 0;
}