#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int V, E;
vector<vector<int>> graph;

void scc(int u, vector<int> & low, vector<int> & label, int & time, vector<vector<int>> & ans, stack<int> & S){
	label[u] = low[u] = ++time;
	S.push(u);
	for(int & v : graph[u]){
		if(!label[v]) scc(v, low, label, time, ans, S);
		low[u] = min(low[u], low[v]);
	}
	if(label[u] == low[u]){
		vector<int> comp;
		while(S.top() != u){
			comp.push_back(S.top());
			low[S.top()] = V + 1;
			S.pop();
		}
		comp.push_back(S.top());
		S.pop();
		ans.push_back(comp);
		low[u] = V + 1;
	}
}

vector<vector<int>> scc(){
	vector<int> low(V), label(V);
	int time = 0;
	vector<vector<int>> ans;
	stack<int> S;
	for(int u = 0; u < V; ++u)
		if(!label[u]) scc(u, low, label, time, ans, S);
	return ans;
}

lli mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int u, v;
	cin >> V;
	vector<int> costs(V);
	graph = vector<vector<int>>(V, vector<int>());
	for(int i = 0; i < V; ++i)
		cin >> costs[i];
	cin >> E;
	for(int i = 0; i < E; ++i){
		cin >> u >> v;
		graph[u - 1].push_back(v - 1);
	}
	vector<vector<int>> components = scc();
	lli ans = 0, ways = 1;
	for(auto & component : components){
		int minimo = 1 << 30;
		for(int & dest : component){
			minimo = min(minimo, costs[dest]);
		}
		ans += minimo;
		int count = 0;
		for(int & dest : component){
			if(costs[dest] == minimo) ++count;
		}
		ways = ways * count % mod;
	}
	cout << ans << " " << ways;
	return 0;
}