#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;
using poly = vector<int>;
using mat = vector<poly>;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

mat inv(mat A, bool& exists){
	int n = A.size();
	mat B(n, poly(n));
	for(int i = 0; i < n; ++i){
		B[i][i] = 1;
	}
	int i = 0, j = 0;
	while(i < n && j < n){
		if(A[i][j] == 0){
			for(int k = i+1; k < n; ++k){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					swap(B[i], B[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			lli inv_mult = powerMod(A[i][j], mod-2);
			for(int l = 0; l < n; ++l){
				A[i][l] = inv_mult * A[i][l] % mod;
				B[i][l] = inv_mult * B[i][l] % mod;
			}
			for(int k = 0; k < n; ++k){
				if(i == k) continue;
				lli pv = A[k][j];
				for(int l = 0; l < n; ++l){
					A[k][l] -= pv * A[i][l] % mod;
					B[k][l] -= pv * B[i][l] % mod;
					if(A[k][l] < 0) A[k][l] += mod;
					if(B[k][l] < 0) B[k][l] += mod;
				}
			}
			i++;
		}
		j++;
	}
	exists = (i == n);
	return B;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	mat A(n, poly(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> A[i][j];
		}
	}
	bool exists = true;
	mat B = inv(A, exists);
	if(exists){
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				cout << B[i][j] << " ";
			}
			cout << "\n";
		}
	}else{
		cout << "-1\n";
	}
	return 0;
}