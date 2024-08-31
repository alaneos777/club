#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;
using vec = vector<int>;
using mat = vector<vec>;

mat operator*(const mat& A, const mat& B){
	int m = A.size(), n = A[0].size(), p = B[0].size();
	mat C(m, vec(p));
	for(int i = 0; i < m; ++i){
		for(int k = 0; k < n; ++k){
			for(int j = 0; j < p; ++j){
				C[i][j] += (lli)A[i][k] * B[k][j] % mod;
				if(C[i][j] >= mod) C[i][j] -= mod;
			}
		}
	}
	return C;
}

mat operator^(mat A, lli k){
	int n = A.size();
	mat ans(n, vec(n));
	for(int i = 0; i < n; ++i){
		ans[i][i] = 1;
	}
	while(k){
		if(k & 1) ans = ans * A;
		A = A * A;
		k >>= 1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n; lli k;
	cin >> n >> k;
	mat A(n, vec(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> A[i][j];
		}
	}
	mat B = A^k;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << B[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}