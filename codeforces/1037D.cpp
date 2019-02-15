#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, u, v;
	cin >> n;
	vector<vector<int>> adj(n+1);
	for(int i = 0; i < n-1; ++i){
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> path(n), perm(n+1);
	for(int i = 0; i < n; ++i){
		cin >> path[i];
		perm[path[i]] = i;
	}
	for(int i = 1; i <= n; ++i){
		sort(adj[i].begin(), adj[i].end(), [&](int a, int b){return perm[a] < perm[b];});
	}
	vector<bool> visited(n+1);
	queue<int> Q;
	Q.push(1);
	visited[1] = true;
	vector<int> bfs;
	bfs.push_back(1);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		for(int v : adj[u]){
			if(!visited[v]){
				visited[v] = true;
				Q.push(v);
				bfs.push_back(v);
			}
		}
	}
	cout << ((path == bfs) ? "Yes\n" : "No\n");
	return 0;
}