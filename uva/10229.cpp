#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef vector< vector<lli> > matriz;

matriz multiplicar(matriz & A, matriz & B, lli mod){
	int n = A.size();
	matriz C(n, vector<lli>(n, 0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
			}
		}
	}
	return C;
}

matriz exp_bin_mod(matriz A, lli b, lli mod){
	int n = A.size();
	matriz ans(n, vector<lli>(n, 0));
	for(int i = 0; i < n; i++){
		ans[i][i] = 1;
	}
	while(b){
		if(b & 1) ans = multiplicar(ans, A, mod);
		b >>= 1;
		A = multiplicar(A, A, mod);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	lli n, m;
	while(cin >> n >> m){
		matriz F(2, vector<lli>(2, 1));
		F[1][1] = 0;
		F = exp_bin_mod(F, n, ((lli)1) << m);
		cout << F[1][0] << "\n";
	}
	return 0;
}