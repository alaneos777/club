#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const uint32_t mod = 1234567891;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 1e7 + 20;
vector<uint32_t> inv(M+1, 1), invfact(M+1, 1);

int inverse(int a){
	if(a <= M) return inv[a];
	int r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += mod;
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 2; i <= M; ++i){
		inv[i] = mod - (lli)(mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)invfact[i-1] * inv[i] % mod;
	}
	int t;
	cin >> t;
	while(t--){
		lli n; int k;
		cin >> n >> k;
		vector<uint32_t> f(k+3), s(k+3);
		for(int i = 1; i <= k+2; ++i){
			f[i] = f[i-1] + power(i, k);
			if(f[i] >= mod) f[i] -= mod;
			s[i] = s[i-1] + f[i];
			if(s[i] >= mod) s[i] -= mod;
		}
		if(n <= k+2){
			cout << s[n] << "\n";
		}else{
			uint32_t ans = 0;
			uint32_t n_ = n % mod;
			for(uint32_t i = 0; i <= k+2; ++i){
				int u = (n_ >= i ? n_ - i : n_ + mod - i);
				uint32_t term = (lli)s[i] * inverse(u) % mod * invfact[i] % mod * invfact[k+2 - i] % mod;
				if(i & 1){
					if(term) ans += mod - term;
				}else{
					ans += term;
				}
				if(ans >= mod) ans -= mod;
			}
			if(k & 1){
				if(ans) ans = mod - ans;
			}
			for(uint32_t i = 0; i <= k+2; ++i){
				int u = (n_ >= i ? n_ - i : n_ + mod - i);
				ans = (lli)ans * u % mod;
			}
			cout << ans << "\n";
		}
	}
	return 0;
}