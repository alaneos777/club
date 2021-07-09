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

lli det(mat A){
	int n = A.size();
	lli ans = 1;
	int i = 0, j = 0;
	while(i < n && j < n){
		if(A[i][j] == 0){
			for(int k = i+1; k < n; ++k){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					ans = (mod - ans) % mod;
					break;
				}
			}
		}
		if(A[i][j] != 0){
			lli inv_mult = powerMod(A[i][j], mod-2);
			ans = ans * A[i][j] % mod;
			for(int l = 0; l < n; ++l){
				A[i][l] = inv_mult * A[i][l] % mod;
			}
			for(int k = 0; k < n; ++k){
				if(i == k) continue;
				lli pv = A[k][j];
				for(int l = 0; l < n; ++l){
					A[k][l] -= pv * A[i][l] % mod;
					if(A[k][l] < 0) A[k][l] += mod;
				}
			}
			i++;
		}
		j++;
	}
	if(i < n) ans = 0;
	return ans;
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
	cout << det(A) << "\n";
	return 0;
}