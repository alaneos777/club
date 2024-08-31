#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;
using poly = vector<int>;
using mat = vector<poly>;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int gauss(mat& A){
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
	int n, m;
	cin >> n >> m;
	mat A(n, poly(m));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			cin >> A[i][j];
		}
	}
    int rank = 0;
    if(m > 0 && n > 0) rank = gauss(A);
	cout << rank << "\n";
	return 0;
}