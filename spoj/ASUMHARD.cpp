#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned int uint;

uint mod = 1234567891;

int inv(int a, int m){
	int r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 == -1) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}

lli exp(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli inv_fact[350];
lli S[400][400];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	uint k, n;
	cin >> t;
	inv_fact[0] = 1;
	for(int i = 1; i < 350; ++i){
		inv_fact[i] = inv_fact[i - 1] * inv(i, mod) % mod;
	}
	for(int k = 0; k < 350; ++k){
		uint f = 0;
		for(int i = 1; i <= k+2; ++i){
			f += exp(i, k, mod);
			if(f >= mod) f -= mod;
			S[k][i] = S[k][i - 1] + f;
			if(S[k][i] >= mod) S[k][i] -= mod;
		}
	}
	while(t--){
		cin >> n >> k;
		uint sum = 0;
		if(n <= k+2){
			sum = S[k][n];
		}else{
			int alt = ((k & 1) ? -1 : 1);
			for(uint i = 0; i <= k+2; ++i){
				uint tmp = S[k][i] * inv_fact[i] % mod * inv_fact[k+2 - i] % mod * inv(n - i, mod) % mod;
				if(alt == 1){
					sum += tmp;
				}else{
					sum += (mod - tmp);
				}
				while(sum >= mod) sum -= mod;
				alt *= -1;
			}
			for(uint i = 0; i <= k+2; ++i){
				sum = (lli)sum * (n - i) % mod;
			}
		}
		cout << sum << "\n";
	}
	return 0;
}