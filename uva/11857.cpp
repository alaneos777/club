#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> edge;

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
    int V, E;
    while(cin >> V >> E){
        if(V == 0 && E == 0) break;
        int cost, u, v;
        vector<edge> edges;
        for(int i = 0; i < E; ++i){
            cin >> u >> v >> cost;
            edges.push_back({cost, {u, v}});
            edges.push_back({cost, {v, u}});
        }
        sort(edges.begin(), edges.end());
        disjointSet DS(V);
        for(int u = 0; u < V; ++u)
            DS.makeSet(u);
        vector<edge> MST;
        int i = 0;
        while(i < edges.size() && MST.size() < V - 1){
            edge current = edges[i++];
            int u = current.second.first, v = current.second.second;
            if(DS.findSet(u) != DS.findSet(v)){
                MST.push_back(current);
                DS.unionSet(u, v);
            }
        }
        if(MST.size() == V - 1) cout << MST.back().first << "\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}