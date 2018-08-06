#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;
typedef vector< vector<double> > matriz;

matriz mult(matriz A, matriz B, int n){
	matriz C(n, vector<double>(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k){
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

matriz exp_bin(matriz A, ull b, int n){
	matriz ans(n, vector<double>(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			ans[i][j] = (i == j ? 1 : 0);
		}
	}
	while(b){
		if(b & 1){
			ans = mult(ans, A, n);
		}
		b >>= 1;
		A = mult(A, A, n);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int N;
	double f0, f1;
	double a, b;
	ull n;
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> f0 >> f1 >> a >> b >> n;
		matriz A = {{a, b}, {1, 0}};
		A = exp_bin(A, n, 2);
		cout << (int)round(A[1][0] * f1 + A[1][1] * f0) << "\n";
	}
	return 0;
}