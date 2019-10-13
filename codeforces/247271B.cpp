#include <bits/stdc++.h>
using namespace std;

struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent, count;

	disjointSet(int N): N(N), parent(N), count(N), rank(N){}

	void makeSet(int v){
		count[v] = 1;
		parent[v] = v;
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
			count[b] += count[a];
		}else{
			parent[b] = a;
			count[a] += count[b];
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	disjointSet DS(n);
	for(int i = 0; i < n; ++i){
		DS.makeSet(i);
	}
	while(m--){
		int k;
		cin >> k;
		vector<int> g(k);
		for(int & gi : g){
			cin >> gi;
			--gi;
		}
		for(int i = 0; i < k-1; ++i){
			DS.unionSet(g[i], g[i+1]);
		}
	}
	for(int i = 0; i < n; ++i){
		if(i) cout << " ";
		cout << DS.count[DS.findSet(i)];
	}
	cout << "\n";
	return 0;
}