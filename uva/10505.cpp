#include <bits/stdc++.h>
using namespace std;

int ans(vector<vector<int>> & graph){
	int V = graph.size();
    vector<int> side(V, -1);
    queue<int> q;
    int ret = 0;
    for (int st = 0; st < V; ++st) {
        if(side[st] != -1) continue;
        q.push(st);
        side[st] = 0;
        vector<int> count(2);
        bool test = true;
        while (!q.empty()) {
            int u = q.front();
            ++count[side[u]];
            q.pop();
            for (int & v : graph[u]) {
                if (side[v] == -1) {
                    side[v] = side[u] ^ 1;
                    q.push(v);
                } else {
                    if(side[v] == side[u]){
                    	test = false;
                    }
                }
            }
        }
        if(test) ret += max(count[0], count[1]);
    }
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int m, V, c, v;
	cin >> m;
	while(m--){
		cin >> V;
		vector<vector<int>> graph(V, vector<int>());
		for(int u = 0; u < V; ++u){
			cin >> c;
			while(c--){
				cin >> v;
				if(v - 1 < graph.size()){
					graph[u].push_back(v - 1);
					graph[v - 1].push_back(u);
				}
			}
		}
		cout << ans(graph) << "\n";
	}
	return 0;
}