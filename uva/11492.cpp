#include <bits/stdc++.h>
using namespace std;

struct edge{
	int source, dest, cost;
	char first;
	bool operator>(const edge & e) const{
		return cost > e.cost;
	}
};

int inf = 1 << 30;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int E;
	string s, d, a, b, word;
	while(cin >> E && E){
		cin >> s >> d;
		map<string, int> mapeo;
		int V = 0;
		vector<edge> edges(E);
		for(int i = 0; i < E; ++i){
			cin >> a >> b >> word;
			if(!mapeo.count(a)) mapeo[a] = V++;
			if(!mapeo.count(b)) mapeo[b] = V++;
			edges[i] = {mapeo[a], mapeo[b], (int)word.size(), word[0]};
		}
		vector<vector<edge>> graph(V, vector<edge>());
		for(int i = 0; i < E; ++i){
			int u = edges[i].source, v = edges[i].dest, cost = edges[i].cost;
			graph[u].push_back({u, v, cost, edges[i].first});
			graph[v].push_back({v, u, cost, edges[i].first});
		}
		if(s == d){
			cout << "0\n";
			continue;
		}
		if(!mapeo.count(s) || !mapeo.count(d)){
			cout << "impossivel\n";
			continue;
		}
		int source = mapeo[s], dest = mapeo[d];
		priority_queue<edge, vector<edge>, greater<edge>> Q;
		vector<vector<int>> costs(V, vector<int>(26, inf));
		Q.push({source, source, 0, 0});
		costs[source] = vector<int>(26, 0);
		while(!Q.empty()){
			int u = Q.top().dest;
			char prev = Q.top().first;
			int prev_cost = Q.top().cost;
			Q.pop();
			for(edge & current : graph[u]){
				int v = current.dest;
				int nuevo = prev_cost + current.cost;
				if(prev != current.first && nuevo < costs[v][current.first - 'a']){
					costs[v][current.first - 'a'] = nuevo;
					Q.push({v, v, nuevo, current.first});
				}
			}
		}
		int ans = *min_element(costs[dest].begin(), costs[dest].end());
		if(ans != inf){
			cout << ans << "\n";
		}else{
			cout << "impossivel\n";
		}
	}
	return 0;
}