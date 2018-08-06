#include <bits/stdc++.h>
using namespace std;

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
	int n, x, y;
	while(cin >> n && n){
		vector<pair<int, int>> points(n);
		for(int i = 0; i < n; ++i){
			cin >> points[i].first >> points[i].second;
		}
		vector<pair<double, pair<int, int>>> edges;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				int x1 = points[i].first, y1 = points[i].second;
				int x2 = points[j].first, y2 = points[j].second;
				if(i != j){
					edges.push_back({hypot(x2 - x1, y2 - y1), {i, j}});
				}
			}
		}
		sort(edges.begin(), edges.end());
		disjointSet DS(n);
		for(int u = 0; u < n; ++u) DS.makeSet(u);
		int i = 0, mst_size = 0;
		double cost = 0;
		while(i < edges.size() && mst_size < n - 1){
			auto current = edges[i++];
			int u = current.second.first, v = current.second.second;
			if(DS.findSet(u) != DS.findSet(v)){
				mst_size++;
				DS.unionSet(u, v);
				cost += current.first;
			}
		}
		cout << fixed << setprecision(2) << cost << "\n";
	}
	return 0;
}