#include <bits/stdc++.h>
using namespace std;

const int mod = 1e6;
const int lim = 3e6;

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
	vector<int> F(1);
	for(int64_t k = 1; k <= 55; ++k){
		int fk = (100003 - 200003*k + 300007*k*k*k) % mod;
		if(fk < 0) fk += mod;
		F.push_back(fk);
	}
	for(int k = 56; k <= 2*lim; ++k){
		F.push_back(F[k - 24] + F[k - 55]);
		if(F.back() >= mod) F.back() -= mod;
	}
	int dials = 0;
	int pm = 524287;
	disjointSet ds(mod);
	for(int i = 0; i < mod; ++i){
		ds.makeSet(i);
	}
	for(int n = 1; n <= lim; ++n){
		int a = F[2*n-1], b = F[2*n];
		if(a == b) continue;
		dials++;
		ds.unionSet(a, b);
		if(ds.count[ds.findSet(pm)] >= 990000){
			cout << dials << "\n";
			break;
		}
	}
	return 0;
}