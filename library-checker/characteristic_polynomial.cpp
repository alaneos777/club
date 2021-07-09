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

int trace(const mat& A, const mat& B){
	int n = A.size();
	int tr = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			tr += (lli)A[i][j] * B[j][i] % mod;
			if(tr >= mod) tr -= mod;
		}
	}
	return tr;
}

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	mat A(n, vec(n)), I(n, vec(n));
	for(int i = 0; i < n; ++i){
		I[i][i] = 1;
		for(int j = 0; j < n; ++j){
			cin >> A[i][j];
		}
	}
	if(n == 0){
		cout << "1\n";
		return 0;
	}
	int m = int(sqrt(n)) + 1;
	vector<mat> lo(m+1), hi(m+1);
	lo[0] = hi[0] = I;
	for(int i = 1; i <= m; ++i){
		lo[i] = lo[i-1] * A;
	}
	for(int i = 1; i <= m; ++i){
		hi[i] = hi[i-1] * lo[m];
	}
	vec P(n+1), S(n+1);
	for(int i = 1; i <= n; ++i){
		mat pw = I;
		P[i] = trace(hi[i/m], lo[i%m]);
		S[i] = P[i];
		for(int j = 1; j < i; ++j){
			if(j & 1) S[i] -= (lli)S[j]*P[i-j] % mod;
			else S[i] += (lli)S[j]*P[i-j] % mod;
			if(S[i] >= mod) S[i] -= mod;
			if(S[i] < 0) S[i] += mod;
		}
		S[i] = S[i] * powerMod(i, mod-2) % mod;
		if((i&1) == 0) S[i] = (mod - S[i]) % mod;
	}
	S[0] = 1;
	for(int i = 1; i <= n; i += 2){
		S[i] = (mod - S[i]) % mod;
	}
	for(int i = n; i >= 0; --i){
		cout << S[i] << " ";
	}
	return 0;
}