#include <bits/stdc++.h>
using namespace std;

struct edge{
	int u, v, cost, pos1, pos2;
	bool operator<(const edge & e){
		return cost < e.cost;
	}
};

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent;

	disjointSet(int N){
		this->N = N;
		parent.resize(N);
		rank.resize(N);
	}

	void makeSet(int v){
		parent[v] = v;
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a);
		b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
		}else{
			parent[b] = a;
			if(rank[a] == rank[b]){
				++rank[a];
			}
		}
	}
};

pair<vector<edge>, int> kruskal(vector<edge> & edges, int V, int ignore){
	int cost = 0;
	vector<edge> MST;
	disjointSet DS(V);
	for(int u = 0; u < V; ++u)
		DS.makeSet(u);
	int i = 0;
	while(i < edges.size() && MST.size() < V - 1){
		edge current = edges[i];
		int u = current.u, v = current.v;
		if(current.pos1 == ignore || current.pos2 == ignore){
			++i;
			continue;
		}
		if(DS.findSet(u) != DS.findSet(v)){
			MST.push_back(current);
			cost += current.cost;
			DS.unionSet(u, v);
		}
		++i;
	}
	return {MST, cost};
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int V, E;
		int u, v, w;
		cin >> V >> E;
		vector<edge> edges;
		for(int i = 0; i < E; ++i){
			cin >> u >> v >> w;
			--u, --v;
			edges.push_back({u, v, w, 2*i, 2*i+1});
			edges.push_back({v, u, w, 2*i, 2*i+1});
		}
		sort(edges.begin(), edges.end());
		auto info1 = kruskal(edges, V, -1);
		cout << "Case #" << caso << " : ";
		if(info1.first.size() == V - 1){
			int cost = 1 << 30;
			vector<edge> best;
			for(edge & current : info1.first){
				auto info2 = kruskal(edges, V, current.pos1);
				if(info2.first.size() == V - 1 && info2.second < cost){
					best = info2.first;
					cost = info2.second;
				}
			}
			if(cost != (1 << 30)){
				cout << cost << "\n";
			}else{
				cout << "No second way\n";
			}
		}else{
			cout << "No way\n";
		}
	}
	return 0;
}