#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;
bool eq(ld a, ld b){return abs(a-b) < eps;}

auto gauss(vector<vector<ld>> & A){
	int n = A.size(), i = 0, j = 0;
	vector<vector<ld>> B(n, vector<ld>(n));
	for(int i = 0; i < n; ++i){
		B[i][i] = 1;
	}
	while(i < n && j < n){
		if(eq(A[i][j], 0)){
			for(int k = i + 1; k < n; k++){
				if(!eq(A[k][j], 0)){
					swap(A[i], A[k]);
					swap(B[i], B[k]);
					break;
				}
			}
		}
		if(!eq(A[i][j], 0)){
			ld inv_mult = 1.0l / A[i][j];
			if(!eq(A[i][j], 1)){
				for(int l = 0; l < n; ++l){
					A[i][l] = A[i][l] * inv_mult;
					B[i][l] = B[i][l] * inv_mult;
				}
			}
			for(int k = 0; k < n; k++){
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
	int n, m, q;
	cin >> n >> m;
	vector<vector<pair<int, int>>> sale(n), entra(n);
	while(m--){
		int u, v, r;
		cin >> u >> v >> r;
		--u, --v;
		sale[u].emplace_back(v, r);
		entra[v].emplace_back(u, r);
	}
	vector<vector<ld>> mat(n-1, vector<ld>(n-1));
	for(int i = 0; i < n-1; ++i){
		for(const auto & par : entra[i]){
			int j, r;
			tie(j, r) = par;
			//(v[j] - v[i])/r
			if(j < n-1) mat[i][j] += 1.0l/r;
			mat[i][i] -= 1.0l/r;
		}
		for(const auto & par : sale[i]){
			int j, r;
			tie(j, r) = par;
			//(v[i] - v[j])/r
			if(j < n-1) mat[i][j] += 1.0l/r;
			mat[i][i] -= 1.0l/r;
		}
	}
	auto inv = gauss(mat);
	cin >> q;
	while(q--){
		int u, v;
		cin >> u >> v;
		--u, --v;
		ld V_u = (u == n-1 ? 0 : -inv[u][u] + (v == n-1 ? 0 : inv[u][v]));
		ld V_v = (v == n-1 ? 0 : (u == n-1 ? 0 : -inv[v][u]) + inv[v][v]);
		cout << fixed << setprecision(8) << abs(V_u - V_v) << "\n";
	}
	return 0;
}