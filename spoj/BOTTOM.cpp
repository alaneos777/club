#include <bits/stdc++.h>
using namespace std;

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
		sort(comp.begin(), comp.end());
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

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int u, v;
	while(cin >> V && V){
		cin >> E;
		graph = vector<vector<int>>(V, vector<int>());
		for(int i = 0; i < E; ++i){
			cin >> u >> v;
			--u, --v;
			graph[u].push_back(v);
		}
		vector<vector<int>> components = scc();
		vector<int> ans;
		for(int i = 0; i < components.size(); ++i){
			bool test = true;
			for(int j = 0; j < components[i].size(); ++j){
				if(!test) break;
				for(int & x : graph[components[i][j]]){
					if(!binary_search(components[i].begin(), components[i].end(), x)){
						test = false;
						break;
					}
				}
			}
			if(test) ans.push_back(i);
		}
		vector<int> sink;
		for(int & c : ans){
			for(int & x : components[c]){
				sink.push_back(x);
			}
		}
		sort(sink.begin(), sink.end());
		for(int & x : sink){
			cout << x+1 << " ";
		}
		cout << "\n";
	}
	return 0;
}