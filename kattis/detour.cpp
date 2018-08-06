#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct edge{
	int source, dest;
	lli cost;
	bool operator>(const edge & e) const{
		return cost > e.cost;
	}
};

lli inf = 1ll << 62;

struct path{
	lli cost = inf;
	int previous = -1;
	int size = 1;
};

int V, E;

void dijkstra(int start, int dest, vector<vector<edge>> & adjList, vector<int> & next){
	priority_queue<edge, vector<edge>, greater<edge>> cola;
	vector<path> paths(V, path());
	vector<bool> relaxed(V, false);
	cola.push({start, start, 0});
	paths[start].cost = 0;
	relaxed[start] = true;
	bool found = false;
	while(!cola.empty()){
		int u = cola.top().dest; cola.pop();
		if(u == dest){
			found = true;
			if(dest != -1) break;
		}
		relaxed[u] = true;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(dest != -1 && next[u] == v) continue;
			if(relaxed[v]) continue;
			lli nuevo = paths[u].cost + current.cost;
			if(nuevo < paths[v].cost){
				paths[v].previous = u;
				paths[v].size = paths[u].size + 1;
				cola.push({v, v, nuevo});
				paths[v].cost = nuevo;
			}
		}
	}
	if(dest == -1){
		for(int i = 0; i < V; ++i){
			next[i] = paths[i].previous;
		}
	}else{
		if(found){
			stack<int> tmp;
			int actual = 1;
			for(int i = 0; i < paths[1].size; ++i){
				tmp.push(actual);
				actual = paths[actual].previous;
			}
			cout << tmp.size();
			while(!tmp.empty()){
				cout << " " << tmp.top();
				tmp.pop();
			}
			cout << "\n";
		}else{
			cout << "impossible\n";
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int u, v;
	lli w;
	cin >> V >> E;
	vector<vector<edge>> graph(V, vector<edge>());
	for(int i = 0; i < E; ++i){
		cin >> u >> v >> w;
		graph[u].push_back({u, v, w});
		graph[v].push_back({v, u, w});
	}
	vector<int> next(V, -1);
	dijkstra(1, -1, graph, next);
	dijkstra(0, 1, graph, next);
	return 0;
}