#include <bits/stdc++.h>
using namespace std;

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent;

	disjointSet(int N): N(N), parent(N), rank(N){
		iota(parent.begin(), parent.end(), 0);
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a), b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
		}else{
			parent[b] = a;
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	disjointSet ds(n);
	while(q--){
		int t, u, v;
		cin >> t >> u >> v;
		if(t == 0){
			ds.unionSet(u, v);
		}else{
			cout << (ds.findSet(u) == ds.findSet(v)) << "\n";
		}
	}
	return 0;
}