#include <bits/stdc++.h>
using namespace std;

struct bs{
	vector<uint64_t> a;
	size_t sz;

	bs(){}
	bs(size_t sz): sz(sz), a((sz + 63) >> 6) {}

	bool operator[](size_t i) const{
		return (a[i >> 6] >> (i & 63)) & 1;
	}

	void set(size_t i){
		a[i >> 6] |= (1ll << (i & 63));
	}

	bs& operator^=(const bs& rhs){
		for(size_t i = 0; i < a.size(); ++i){
			a[i] ^= rhs.a[i];
		}
		return *this;
	}
};

int dim(vector<bs> A){
	int m = A.size(), n = A[0].sz, i = 0, j = 0;
	while(i < m && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < m; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			for(int k = i + 1; k < m; k++){
				if(A[k][j] != 0){
					A[k] ^= A[i];
				}
			}
			i++;
		}
		j++;
	}
	return i;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	while(m--){
		int u, v;
		cin >> u >> v;
		--u; --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<bs> equations(n, bs(n+1));
	for(int u = 0; u < n; ++u){
		int sz = adj[u].size();
		if(sz & 1) equations[u].set(u);
		for(int v : adj[u]){
			equations[u].set(v);
		}
	}
	int rankA = dim(equations);
	for(int u = 0; u < n; ++u){
		int sz = adj[u].size();
		if(!(sz & 1)) equations[u].set(n);
	}
	int rankC = dim(equations);
	if(rankA < rankC){
		cout << "N\n";
	}else{
		cout << "Y\n";
	}
	return 0;
}