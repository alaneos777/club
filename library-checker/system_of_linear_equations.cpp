#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int gauss(vector<vector<lli>>& A){
	int m = A.size(), n = A[0].size(), i = 0, j = 0;
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
			lli inv_mult = power(A[i][j], mod - 2);
			if(A[i][j] != 1){
				for(int l = 0; l < n; ++l){
					A[i][l] = A[i][l] * inv_mult % mod;
				}
			}
			for(int k = 0; k < m; k++){
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
	int m, n;
	cin >> m >> n;
	vector<vector<lli>> A(m, vector<lli>(n+1));
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cin >> A[i][j];
		}
	}
	for(int i = 0; i < m; ++i){
		cin >> A[i][n];
	}

	int rank_augmented = gauss(A), rank = 0;
	vector<int> pivot(m);
	vector<bool> is_free(n, true);
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(A[i][j] != 0){
				pivot[i] = j;
				is_free[j] = false;
				rank++;
				break;
			}
		}
	}
	pivot.resize(rank);

	if(rank < rank_augmented){
		cout << "-1\n";
		return 0;
	}

	vector<lli> ans(n);
	for(int i = 0; i < rank; ++i){
		ans[pivot[i]] = A[i][n];
	}

	int nullity = n - rank;
	vector<vector<lli>> kernel(nullity, vector<lli>(n));
	int sz = 0;
	for(int j = 0; j < n; ++j){
		if(is_free[j]){
			int idx_col = 0;
			for(int i = 0; i < n; ++i){
				if(is_free[i]){
					if(i == j) kernel[sz][i] = 1;
				}else{
					kernel[sz][i] = (mod - A[idx_col++][j]) % mod;
				}
			}
			sz++;
		}
	}

	cout << nullity << "\n";
	for(int i = 0; i < n; ++i){
		cout << ans[i] << " ";
	}
	cout << "\n";
	for(int i = 0; i < nullity; ++i){
		for(int j = 0; j < n; ++j){
			cout << kernel[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}