#include <bits/stdc++.h>
using namespace std;

struct disjointSet{
    int N;
    vector<short int> rank;
    vector<int> parent, count;

    disjointSet(int N){
        this->N = N;
        parent.resize(N);
        rank.resize(N);
        count.resize(N);
    }

    void makeSet(int v){
    	count[v] = 1;
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
            count[b] += count[a];
        }else{
            parent[b] = a;
            count[a] += count[b];
            if(rank[a] == rank[b]){
                ++rank[a];
            }
        }
    }
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t, f;
	string p1, p2;
	cin >> t;
	while(t--){
		int pos = 0;
		unordered_map<string, int> mapeo;
		cin >> f;
		vector<pair<string, string>> info(f);
		for(int i = 0; i < f; ++i){
			cin >> p1 >> p2;
			info[i] = {p1, p2};
			if(mapeo.count(p1) == 0) mapeo[p1] = pos++;
			if(mapeo.count(p2) == 0) mapeo[p2] = pos++;
		}
		disjointSet DS(pos);
		for(int i = 0; i < pos; ++i){
			DS.makeSet(i);
		}
		for(int i = 0; i < f; ++i){
			int u = mapeo[info[i].first], v = mapeo[info[i].second];
			DS.unionSet(u, v);
			cout << DS.count[DS.findSet(u)] << "\n";
		}
	}
	return 0;
}