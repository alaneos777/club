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
        while (!q.empty()) {
            int u = q.front();
            ++count[side[u]];
            q.pop();
            for (int & v : graph[u]) {
                if (side[v] == -1) {
                    side[v] = side[u] ^ 1;
                    q.push(v);
                } else {
                    if(side[v] == side[u]) return -1;
                }
            }
        }
        if(count[0] + count[1] == 1){
        	++ret;
        }else{
        	ret += min(count[0], count[1]);
        }
    }
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t, v, e, s, d;
	cin >> t;
	while(t--){
		cin >> v >> e;
		vector<vector<int>> graph(v, vector<int>());
		while(e--){
			cin >> s >> d;
			graph[s].push_back(d);
			graph[d].push_back(s);
		}
		cout << ans(graph) << "\n";
	}
	return 0;
}