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
        int pos = 0, cost;
        map<string, int> mapeo;
        string str, str2;
        for(int i = 0; i < V; ++i){
            cin >> str;
            mapeo[str] = pos++;
        }
        vector<edge> edges;
        for(int i = 0; i < E; ++i){
            cin >> str >> str2 >> cost;
            int u = mapeo[str], v = mapeo[str2];
            edges.push_back({cost, {u, v}});
            edges.push_back({cost, {v, u}});
        }
        cin >> str;
        sort(edges.begin(), edges.end());
        disjointSet DS(V);
        for(int u = 0; u < V; ++u)
            DS.makeSet(u);
        int i = 0, mstSize = 0, ans = 0;
        while(i < edges.size() && mstSize < V - 1){
            edge current = edges[i++];
            int u = current.second.first, v = current.second.second;
            if(DS.findSet(u) != DS.findSet(v)){
                ans += current.first;
                ++mstSize;
                DS.unionSet(u, v);
            }
        }
        if(mstSize == V - 1) cout << ans << "\n";
        else cout << "Impossible\n";
    }
    return 0;
}