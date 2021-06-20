#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int gauss(vector<vector<lli>> A, lli mod){
	int n = A.size(), i = 0, j = 0;
	while(i < n && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < n; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			lli inv_mult = power(A[i][j], mod - 2, mod);
			if(A[i][j] != 1){
				for(int l = 0; l < n; ++l){
					A[i][l] = A[i][l] * inv_mult % mod;
				}
			}
			for(int k = 0; k < n; k++){
				if(k != i && A[k][j] != 0){
					lli inv_adit = (mod - A[k][j]) % mod;
					for(int l = 0; l < n; ++l){
						A[k][l] += inv_adit * A[i][l] % mod;
						if(A[k][l] >= mod) A[k][l] -= mod;
					}
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
	for(int caso = 1; caso <= t; ++caso){
		int n, m, k;
		cin >> n >> m >> k;
		vector<vector<int>> adj(n);
		for(int i = 0; i < m; ++i){
			int u, v;
			cin >> u >> v;
			adj[u-1].push_back(v-1);
			adj[v-1].push_back(u-1);
		}
		vector<vector<lli>> A(n, vector<lli>(n));
		for(int i = 0; i < n; ++i){
			for(int v : adj[i]){
				A[i][v] += 1;
			}
			A[i][i] -= 1;
			if(A[i][i] < 0) A[i][i] += k;
		}
		int nullity = n - gauss(A, k);
		int ans = power(k, nullity, mod);
		cout << "Case " << caso << ": " << ans << "\n";
	}
	return 0;
}