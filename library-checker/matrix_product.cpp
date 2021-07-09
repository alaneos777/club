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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	mat A(n, vec(m)), B(m, vec(k));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			cin >> A[i][j];
		}
	}
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < k; ++j){
			cin >> B[i][j];
		}
	}
	mat C = A*B;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < k; ++j){
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}