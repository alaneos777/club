#include <bits/stdc++.h>
using namespace std;

bool test(vector<vector<int>> & graph){
	int n = graph.size();

	vector<int> side(n, -1);
	bool is_bipartite = true;
	queue<int> q;
	for (int st = 0; st < n; ++st) {
	    if (side[st] == -1) {
	        q.push(st);
	        side[st] = 0;
	        while (!q.empty()) {
	            int v = q.front();
	            q.pop();
	            for (int u : graph[v]) {
	                if (side[u] == -1) {
	                    side[u] = side[v] ^ 1;
	                    q.push(u);
	                } else {
	                    is_bipartite &= side[u] != side[v];
	                }
	            }
	        }
	    }
	}
	return is_bipartite;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, l, u, v;
	while(cin >> n){
		if(n == 0) break;
		vector<vector<int>> graph(n, vector<int>());
		cin >> l;
		while(l--){
			cin >> u >> v;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		cout << (test(graph) ? "BICOLORABLE." : "NOT BICOLORABLE.") << "\n";
	}
	return 0;
}