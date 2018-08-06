#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int mod = 1e9 + 7;

int inv(int a, int m){
	int r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(abs(r0) == 1);
	if(r0 == -1) s0 *= -1;
	return s0;
}

lli modPow(lli a, int b, int m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli inv_2 = 0;

int answer(int c, lli k){
	int k0 = k % (mod - 1);
	k %= mod;
	int P = 0;
	lli comb = 1;
	for(int i = 0; i < c; ++i){
		int term = c - i;
		if(term & 1) term -= 1;
		P += comb * term % mod;
		if(P >= mod) P -= mod;
		if(P < 0) P += mod;
		comb = comb * (k - i) % mod * inv(i + 1, mod) % mod;
	}
	P = P * modPow(inv_2, k0, mod) % mod;
	P = (c - inv_2) % mod - P;
	if(P >= mod) P -= mod;
	while(P < 0) P += mod;
	return P;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int c; lli k;
	inv_2 = inv(2, mod);
	if(inv_2 < 0) inv_2 += mod;
	cin >> c >> k;
	if(k <= c)
		cout << k * inv_2 % mod;
	else
		cout << answer(c, k);
	return 0;
}