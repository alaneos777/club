#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
};

double dist(point & a, point & b){
	return hypot(a.x - b.x, a.y - b.y);
}

struct edge{
	int u, v;
	double cost;
	bool operator<(const edge & e) const{
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

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int V, E, u, v;
	while(cin >> V){
		vector<point> points(V);
		disjointSet DJ(V);
		for(int i = 0; i < V; ++i){
			cin >> points[i].x >> points[i].y;
			DJ.makeSet(i);
		}
		vector<edge> edges;
		for(int i = 0; i < V - 1; ++i){
			for(int j = i + 1; j < V; ++j){
				edges.push_back({i, j, dist(points[i], points[j])});
			}
		}
		cin >> E;
		vector<edge> MST;
		map<pair<int, int>, bool> already;
		for(int i = 0; i < E; ++i){
			cin >> u >> v;
			--u, --v;
			if(u > v) swap(u, v);
			already[{u, v}] = true;
			if(DJ.findSet(u) != DJ.findSet(v)){
				MST.push_back({u, v, dist(points[u], points[v])});
				DJ.unionSet(u, v);
			}
		}
		sort(edges.begin(), edges.end());
        int i = 0;
        while(i < edges.size() && MST.size() < V - 1){
            edge current = edges[i++];
            int u = current.u, v = current.v;
            if(already[{u, v}]) continue;
            if(DJ.findSet(u) != DJ.findSet(v)){
                MST.push_back(current);
                DJ.unionSet(u, v);
            }
        }
        double ans = 0;
        for(edge & current : MST){
        	if(!already[{current.u, current.v}]) ans += current.cost;
        }
        cout << fixed << setprecision(2) << ans << "\n";
	}
	return 0;
}