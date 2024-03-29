#include <bits/stdc++.h>
using namespace std;

struct bs{
	vector<uint64_t> a;
	size_t sz;

	bs(){}
	bs(size_t sz): sz(sz), a((sz + 63) >> 6) {}

	bool operator[](size_t i) const{
		return (a[i >> 6] >> (63-(i & 63))) & 1;
	}

	bool operator>(const bs& rhs) const{
		return a > rhs.a;
	}

	void set(size_t i){
		a[i >> 6] |= (1ll << (63-(i & 63)));
	}

	void flip(size_t i){
		a[i >> 6] ^= (1ll << (63-(i & 63)));
	}

	bs& operator^=(const bs& rhs){
		for(size_t i = 0; i < a.size(); ++i){
			a[i] ^= rhs.a[i];
		}
		return *this;
	}
};

int gauss(vector<bs> & A){
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
			for(int k = 0; k < m; k++){
				if(k != i && A[k][j] != 0){
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
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		vector<vector<int>> adj(n);
		for(int i = 0; i < m; ++i){
			int u, v;
			cin >> u >> v;
			--u, --v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		vector<bs> A(n, bs(n+1));
		bool simple = true;
		for(int u = 0; u < n; ++u){
			int sz = adj[u].size();
			if(sz & 1){
				A[u].set(u);
				A[u].set(n);
			}
			simple &= (sz % 2 == 0);
			for(int v : adj[u]){
				A[u].set(v);
			}
		}
		if(simple){
			cout << "1\n";
			for(int i = 0; i < n; ++i){
				cout << "1 ";
			}
			cout << "\n";
		}else{
			int rank_augmented = gauss(A), rank = 0;
			vector<int> pivot(m);
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					if(A[i][j]){
						pivot[i] = j;
						rank++;
						break;
					}
				}
			}
			assert(rank == rank_augmented);
			bs ans(n);
			for(int i = 0; i < rank; ++i){
				if(A[i][n]){
					ans.set(pivot[i]);
				}
			}
			cout << "2\n";
			for(int i = 0; i < n; ++i){
				cout << 2-ans[i] << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}