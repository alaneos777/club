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
	int t, V, E, c;
	cin >> t;
	string str1, str2;
	while(t--){
		unordered_map<string, int> mapeo;
		int index = 0;
		cin >> V >> E;
		vector<edge> edges(E << 1);
		for(int i = 0; i < E; ++i){
			cin >> str1 >> str2 >> c;
			if(!mapeo.count(str1)) mapeo[str1] = index++;
			if(!mapeo.count(str2)) mapeo[str2] = index++;
			edges[i << 1] = {c, {mapeo[str1], mapeo[str2]}};
			edges[i << 1 | 1] = {c, {mapeo[str2], mapeo[str1]}};
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
                ans += current.first;
                DS.unionSet(u, v);
            }
        }
        cout << ans << "\n";
        if(t) cout << "\n";
	}
	return 0;
}