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
	int u, v, ans = 0;
	disjointSet DS0(1e5 + 1);
	for(int i = 0; i <= 1e5; ++i){
		DS0.makeSet(i);
	}
	disjointSet DS = DS0;
	while(cin >> u){
		if(u == -1){
			cout << ans << "\n";
			DS = DS0;
			ans = 0;
		}else{
			cin >> v;
			if(DS.findSet(u) == DS.findSet(v)) ++ans;
			DS.unionSet(u, v);
		}
	}
	return 0;
}