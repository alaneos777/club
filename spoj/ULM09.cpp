#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> label;
typedef pair<int, label> edge;

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
    int V, E, x, y, z;
    while(cin >> V >> E){
        if(V == 0 && E == 0) break;
        vector<edge> edges(E << 1);
        int cost = 0;
        for(int i = 0; i < E; ++i){
            cin >> x >> y >> z;
            edges[i << 1] = {z, {x, y}};
            edges[i << 1 | 1] = {z, {y, x}};
            cost += z;
        }
        sort(edges.begin(), edges.end());
        disjointSet DS(V);
        for(int u = 0; u < V; ++u)
            DS.makeSet(u);
        int i = 0, mstSize = 0, ans = 0;
        while(i < edges.size() && mstSize < V - 1){
            auto current = edges[i++];
            int u = current.second.first, v = current.second.second;
            if(DS.findSet(u) != DS.findSet(v)){
                ++mstSize;
                cost -= current.first;
                DS.unionSet(u, v);
            }
        }
        cout << cost << "\n";
    }
    return 0;
}