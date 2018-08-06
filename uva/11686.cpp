#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
int n;

vector<int> topologicalSort(){
    vector<int> order;
    int visited = 0;
    vector<int> indegree(n);
    for(auto & node : graph){
        for(int & dest : node){
            ++indegree[dest];
        }
    }
    queue<int> Q;
    for(int i = 0; i < n; ++i){
        if(indegree[i] == 0) Q.push(i);
    }
    while(!Q.empty()){
        int source = Q.front();
        Q.pop();
        order.push_back(source);
        ++visited;
        for(int & dest : graph[source]){
            --indegree[dest];
            if(indegree[dest] == 0) Q.push(dest);
        }
    }
    if(visited == n) return order;
    else return {};
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int m, u, v;
	while(cin >> n >> m){
		if(n == 0 && m == 0) break;
		graph = vector<vector<int>>(n, vector<int>());
		for(int i = 0; i < m; ++i){
			cin >> u >> v;
			graph[u - 1].push_back(v - 1);
		}
		vector<int> order = topologicalSort();
		if(order.size()){
			for(int & x : order) cout << x + 1 << "\n";
		}else{
			cout << "IMPOSSIBLE\n";
		}
	}
	return 0;
}