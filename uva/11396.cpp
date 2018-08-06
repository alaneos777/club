#include <bits/stdc++.h>
using namespace std;

bool isBipartite(vector<vector<int>> & adjList){
	int V = adjList.size();
    vector<int> side(V, -1);
    queue<int> q;
    for (int st = 0; st < V; ++st) {
        if(side[st] != -1) continue;
        q.push(st);
        side[st] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int & v: adjList[u]) {
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
	int V, a, b;
	while(cin >> V && V){
		vector<vector<int>> graph(V, vector<int>());
		while(cin >> a >> b && a && b){
			graph[a - 1].push_back(b - 1);
			graph[b - 1].push_back(a - 1);
		}
		if(isBipartite(graph)) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}