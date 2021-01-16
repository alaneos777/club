#include <bits/stdc++.h>
using namespace std;
 
bool isBipartite(const vector<vector<int>> & adj){
	int n = adj.size();
	vector<int> side(n, -1);
	queue<int> q;
	for(int st = 0; st < n; ++st){
		if(side[st] != -1) continue;
		q.push(st);
		side[st] = 0;
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int v : adj[u]){
				if(side[v] == -1) {
					side[v] = side[u] ^ 1;
					q.push(v);
				}else{
					if(side[v] == side[u]) return false;
				}
			}
		}
	}
	return true;
}
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int n, m;
		cin >> n >> m;
		vector<vector<int>> adj(n);
		while(m--){
			int u, v;
			cin >> u >> v;
			--u, --v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		cout << "Scenario #" << caso << ":\n";
		if(isBipartite(adj)){
			cout << "No suspicious bugs found!\n";
		}else{
			cout << "Suspicious bugs found!\n";
		}
	}
	return 0;
}