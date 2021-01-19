#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 40353607;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli inv(lli a){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += mod;
	return s0;
}

const lli N = 1e18;

int main(){
	lli ans = (powerMod(4, N+1) - 1) * inv(3) % mod;
	ans += 2 * (powerMod(2, N+1) - 1) % mod;
	ans -= (powerMod(3, N+1) - 1) * inv(2) % mod;
	ans %= mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}