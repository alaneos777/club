#include <bits/stdc++.h>
using namespace std;

void DFS(int start, int source, vector<vector<int>> & graph, vector<vector<bool>> & tmp){
	for(int & current : graph[source]){
		if(!tmp[start][current]){
			tmp[start][current] = true;
			DFS(start, current, graph, tmp);
		}
	}
}

vector<vector<bool>> transitiveClosure(vector<vector<int>> & graph){
	vector<vector<bool>> tmp(graph.size(), vector<bool>(graph.size(), false));
	for(int i = 0; i < graph.size(); i++){
		DFS(i, i, graph, tmp);
	}
	return tmp;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	while(cin >> n){
		if(n == 0) break;
		vector<vector<int>> graph(n, vector<int>());
		int source;
		while(cin >> source){
			if(source == 0) break;
			source--;
			int dest;
			while(cin >> dest){
				if(dest == 0) break;
				dest--;
				graph[source].push_back(dest);
			}
		}
		vector<vector<bool>> tc = transitiveClosure(graph);
		int q;
		cin >> q;
		while(q--){
			cin >> source;
			source--;
			vector<int> ans;
			for(int i = 0; i < n; i++){
				if(!tc[source][i]) ans.push_back(i);
			}
			cout << ans.size();
			for(int i = 0; i < ans.size(); i++){
				cout << " " << ans[i] + 1;
			}
			cout << "\n";
		}
	}
	return 0;
}