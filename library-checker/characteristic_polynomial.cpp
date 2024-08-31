#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

#include <bits/stdc++.h>
using namespace std;
using lli = unsigned long long int;
const lli mod = 998244353;
const lli mod_2 = mod*mod;
using vec = vector<lli>;
using mat = vector<vec>;

mat operator*(const mat& A, const mat& B){
	int m = A.size(), n = A[0].size(), p = B[0].size();
	mat C(m, vec(p));
	for(int i = 0; i < m; ++i){
		for(int k = 0; k < n; ++k){
			for(int j = 0; j < p; ++j){
                lli prod = A[i][k] * B[k][j];
				C[i][j] += prod;
                C[i][j] = min(C[i][j], C[i][j] - mod_2);
			}
		}
	}
    for(vec& row : C){
        for(lli& x : row){
            if(x >= mod) x %= mod;
        }
    }
	return C;
}

lli trace(const mat& A, const mat& B){
	int n = A.size();
	lli tr = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			tr += A[i][j] * B[j][i] % mod;
			tr = min(tr, tr - mod);
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
			if(j & 1){
                S[i] -= S[j]*P[i-j] % mod;
			    S[i] = min(S[i], S[i] + mod);
            }else{
                S[i] += S[j]*P[i-j] % mod;
                S[i] = min(S[i], S[i] - mod);
            }
		}
		S[i] = S[i] * powerMod(i, mod-2) % mod;
		if((i&1) == 0) S[i] = min(-S[i], mod - S[i]);
	}
	S[0] = 1;
	for(int i = 1; i <= n; i += 2){
		S[i] = min(-S[i], mod - S[i]);
	}
	for(int i = n; i >= 0; --i){
		cout << S[i] << " ";
	}
    cout << "\n";
	return 0;
}