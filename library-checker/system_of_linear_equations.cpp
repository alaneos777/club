#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;
using vec = vector<int>;
using mat = vector<vec>;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

pair<int, int> gauss(mat& A, vec& b){
	int m = A.size(), n = A[0].size();
	assert(b.size() == m);
	int i = 0, j = 0;
	while(i < m && j < n){
		if(A[i][j] == 0){
			for(int k = i+1; k < m; ++k){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					swap(b[i], b[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			lli inv_mult = powerMod(A[i][j], mod-2);
			for(int l = 0; l < n; ++l){
				A[i][l] = inv_mult * A[i][l] % mod;
			}
			b[i] = inv_mult * b[i] % mod;
			for(int k = 0; k < m; ++k){
				if(i == k) continue;
				lli pv = A[k][j];
				for(int l = 0; l < n; ++l){
					A[k][l] -= pv * A[i][l] % mod;
					if(A[k][l] < 0) A[k][l] += mod;
				}
				b[k] -= pv * b[i] % mod;
				if(b[k] < 0) b[k] += mod;
			}
			i++;
		}
		j++;
	}
	int rank_A = i, rank_Ab = i;
	if(i < m && j <= n && b[i] != 0) rank_Ab++;
	return {rank_A, rank_Ab};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, n;
	cin >> m >> n;
	mat A(m, vec(n));
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cin >> A[i][j];
		}
	}
	vec b(m);
	for(int i = 0; i < m; ++i){
		cin >> b[i];
	}

	auto[rank, rank_augmented] = gauss(A, b);
	if(rank < rank_augmented){
		cout << "-1\n";
		return 0;
	}
	int nullity = n - rank;
	vector<int> pivot(m, -1);
	vector<bool> is_free(n, true);
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(A[i][j] == 1){
				is_free[j] = false;
				pivot[i] = j;
				break;
			}
		}
	}
	pivot.resize(rank);

	vec x(n);
	for(int i = 0; i < rank; ++i){
		x[pivot[i]] = b[i];
	}

	mat kernel(nullity, vec(n));
	int sz = 0;
	for(int j = 0; j < n; ++j){
		if(!is_free[j]) continue;
		int idx_row = 0;
		for(int i = 0; i < n; ++i){
			if(is_free[i]){
				if(i == j) kernel[sz][i] = 1;
			}else{
				kernel[sz][i] = (mod - A[idx_row][j]) % mod;
				idx_row++;
			}
		}
		sz++;
	}

	cout << nullity << "\n";
	for(int i = 0; i < n; ++i){
		cout << x[i] << " ";
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