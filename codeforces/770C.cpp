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
	int n, k, t, j;
	cin >> n >> k;
	vector<int> principal(k);
	for(int i = 0; i < k; ++i){
		cin >> principal[i];
		--principal[i];
	}
	vector<vector<int>> graph(n, vector<int>());
	vector<int> color(n);
	for(int i = 0; i < n; ++i){
		cin >> t;
		while(t--){
			cin >> j;
			graph[i].push_back(j - 1);
		}
	}
	vector<int> order;
	for(int & u : principal){
		dfs(u, graph, color, order);
	}
	if(cycle){
		cout << "-1";
	}else{
		cout << order.size() << "\n";
		for(int & u : order){
			cout << u + 1 << " ";
		}
	}
	return 0;
}