#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-9;
 
bool eq(ld a, ld b){return abs(a-b) < eps;}
 
vector<vector<ld>> inverse(vector<vector<ld>> & A){
	int m = A.size(), n = A[0].size(), i = 0, j = 0;
	vector<vector<ld>> B(m, vector<ld>(n));
	for(int d = 0; d < m && d < n; ++d){
		B[d][d] = 1;
	}
	while(i < m && j < n){
		if(eq(A[i][j], 0)){
			for(int k = i+1; k < m; ++k){
				if(!eq(A[k][j], 0)){
					swap(A[i], A[k]);
					swap(B[i], B[k]);
					break;
				}
			}
		}
		if(!eq(A[i][j], 0)){
			ld inv_mult = 1.0l / A[i][j];
			for(int l = 0; l < n; ++l){
				A[i][l] *= inv_mult;
				B[i][l] *= inv_mult;
			}
			for(int k = 0; k < m; ++k){
				if(k != i && !eq(A[k][j], 0)){
					ld inv_adit = -A[k][j];
					for(int l = 0; l < n; ++l){
						A[k][l] += inv_adit * A[i][l];
						B[k][l] += inv_adit * B[i][l];
					}
				}
			}
			i++;
		}
		j++;
	}
	return B;
}
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, start, end;
		cin >> n >> start >> end;
		--start, --end;
		vector<vector<pair<int, int>>> adj(n);
		for(int i = 0; i < n-1; ++i){
			int u, v, w;
			cin >> u >> v >> w;
			adj[u-1].emplace_back(v-1, w);
			adj[v-1].emplace_back(u-1, w);
		}
		if(n == 1 || start == end){
			cout << fixed << setprecision(5) << 0.0l << "\n";
			continue;
		}
		vector<vector<ld>> mat(n-1, vector<ld>(n-1));
		auto id = [&](int x){
			if(x < end) return x;
			return x-1;
		};
		for(int u = 0; u < n; ++u){
			if(u == end) continue;
			ld den = 0;
			for(const auto & e : adj[u]){
				den += e.second;
			}
			for(const auto & e : adj[u]){
				if(e.first == end) continue;
				mat[id(u)][id(e.first)] = -e.second / den;
			}
		}
		for(int i = 0; i < n-1; ++i){
			mat[i][i] += 1;
		}
		mat = inverse(mat);
		ld ans = 0;
		for(int j = 0; j < n-1; ++j){
			ans += mat[id(start)][j];
		}
		cout << fixed << setprecision(5) << ans << "\n";
	}
	return 0;
}