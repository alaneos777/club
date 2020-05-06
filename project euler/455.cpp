#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli inverse(lli a, lli m){
	lli q, r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		q = r0 / r1;
		ri = r0 % r1, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
	}
	if(r0 != 1) return -1;
	if(s0 < 0) s0 += m;
	return s0;
}

lli linear(lli lhs, lli rhs, lli mod){
	lli div = __gcd(lhs, rhs);
	lhs /= div, rhs /= div, mod /= __gcd(mod, div);
	lli inv_lhs = inverse(lhs, mod);
	if(inv_lhs == -1) return -1;
	return inv_lhs * rhs % mod;
}

const int mod = 1e9;
const int m = pow(5, 9);
const int phi_m = m / 5 * 4;
int Log[m];
const int g_m = 2;
const lli crt_2 = (lli)m * inverse(m, 512) % mod;
const lli crt_5 = 512ll * inverse(512, m) % mod;
const int M = 1e6;
int res_5[4*m], period_5[4*m];
int res_2[512], ans[M+1];

int main(){
	memset(Log, -1, sizeof(Log));
	memset(res_5, -1, sizeof(res_5));
	memset(res_2, -1, sizeof(res_2));
	int g_pow = 1;
	for(int i = 0; i < phi_m; ++i){
		Log[g_pow] = i;
		g_pow = (lli)g_pow * g_m % m;
	}
	for(int x = 4*m-1; x >= 0; --x){
		int x_5 = x % m;
		if(Log[x_5] == -1) continue;
		int r = Log[x_5];
		int p = linear(x, r, phi_m);
		if(p == -1) continue;
		period_5[x] = phi_m / __gcd(phi_m, __gcd(x, r));
		res_5[x] = power(g_m, p, m);
	}
	for(int x = 0; x < 512; ++x){
		for(int n = 511; n >= 0; --n){
			if(power(n, x, 512) == x){
				res_2[x] = n;
				break;
			}
		}
	}
	for(int x = 0; x < mod; ++x){
		int n_5 = res_5[x % (4*m)];
		if(n_5 == -1) continue;
		int n_2 = res_2[x % 512];
		if(n_2 == -1) continue;
		int n = n_2 * crt_2 % mod + n_5 * crt_5 % mod;
		if(n >= mod) n -= mod;
		if(n <= M){
			ans[n] = x;
		}
	}
	for(int x = 0; x < mod; x += 512){
		int idx = x % (4*m);
		int n_5 = res_5[idx];
		if(n_5 == -1) continue;
		int period = period_5[idx];
		if(period == phi_m) continue;
		int n_sols = phi_m / period;
		lli inc = power(g_m, period, m);
		for(int i = 0; i < n_sols; ++i){
			// n = 0 mod 2
			// n = n_5 mod m
			for(int n = n_5; n <= M; n += m){
				if(n % 2 == 0) ans[n] = x;
			}
			n_5 = n_5 * inc % m;
		}
	}
	for(int x = 0; x < mod; x += m){
		int n_2 = res_2[x % 512];
		if(n_2 == -1) continue;
		// n = 0 mod 5
		// n = n_2 mod 512
		for(int n = n_2; n <= M; n += 512){
			if(n % 5 == 0) ans[n] = x;
		}
	}
	lli sum = 0;
	for(int n = 2; n <= M; ++n){
		if(n % 10 == 0) continue;
		sum += ans[n];
		//assert(power(n, ans[n], mod) == ans[n]);
	}
	cout << sum << "\n";
	return 0;
}