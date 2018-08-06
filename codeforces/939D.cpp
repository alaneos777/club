#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> edge;

struct disjointSet{
    int N;
    int sets;
    vector<short int> rank;
    vector<int> parent;

    disjointSet(int N){
        this->N = N;
        parent.resize(N);
        rank.resize(N);
    }

    void makeSet(int v){
        parent[v] = v;
        ++sets;
    }

    int findSet(int v){
        if(v == parent[v]) return v;
        return parent[v] = findSet(parent[v]);
    }

    void unionSet(int a, int b){
        a = findSet(a);
        b = findSet(b);
        if(a == b) return;
        --sets;
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
	int n;
	string s1, s2;
	cin >> n >> s1 >> s2;
	vector<edge> edges(n << 1);
	for(int i = 0; i < n; ++i){
		int u = s1[i] - 'a', v = s2[i] - 'a';
		edges[i << 1] = {u, v};
		edges[i << 1 | 1] = {v, u};
	}
	vector<edge> MST;
	disjointSet DS(26);
	for(int i = 0; i < 26; ++i){
		DS.makeSet(i);
	}
	int i = 0;
    while(i < edges.size() && MST.size() < 26 - 1){
        edge current = edges[i++];
        int u = current.first, v = current.second;
        if(DS.findSet(u) != DS.findSet(v)){
            MST.push_back(current);
            DS.unionSet(u, v);
        }
    }
    cout << MST.size() << "\n";
    for(int i = 0; i < MST.size(); ++i){
    	cout << (char)(MST[i].first + 'a') << " " << (char)(MST[i].second + 'a') << "\n";
    }
	return 0;
}