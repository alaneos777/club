#include <bits/stdc++.h>
using namespace std;

bool cycle = false;

void dfs(int u, vector<vector<int>> & graph, vector<int> & color, vector<int> & order){
	if(color[u] == 0){
		color[u] = 1;
		for(int & v : graph[u]) dfs(v, graph, color, order);
		color[u] = 2;
		order.push_back(u);
	}else if(color[u] == 1){
		cycle = true;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	string name;
	cin >> n;
	vector<vector<int>> names(n, vector<int>(100));
	for(int i = 0; i < n; ++i){
		cin >> name;
		for(int j = 0; j < name.size(); ++j){
			names[i][j] = name[j] - 96;
		}
	}
	vector<vector<int>> graph(27, vector<int>());
	for(int i = 1; i < 27; ++i) graph[0].push_back(i);
	for(int i = 0; i < n - 1; ++i){
		int j = 0;
		while(j < 100 && names[i][j] == names[i + 1][j]){
			++j;
		}
		if(j < 100){
			graph[names[i][j]].push_back(names[i + 1][j]);
			//cout << (char)(names[i][j]+96) << "->" << (char)(96+names[i+1][j]) << "\n";
		}
	}
	vector<int> order, color(27);
	for(int i = 0; i < 27; ++i){
		dfs(i, graph, color, order);
	}
	if(cycle) cout << "Impossible";
	else
	for(int i = order.size() - 1; i >= 0; --i){
		char c = order[i] + 96;
		if(c > 96) cout << c;
	}
	return 0;
}