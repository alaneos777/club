#include <iostream>
#include <vector>
#include <map>
#include <cassert>
using namespace std;
using lli = __int128;

const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli inverse(lli a){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += mod;
	return s0;
}

lli ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	r = min(r, n - r);
	lli ans = 1;
	for(lli den = 1, num = n; den <= r; den++, num--)
		ans = ans * num % mod * inverse(den) % mod;
	return ans;
}

lli solve(lli n, int k, int b){
	map<lli, lli> P;
	P[0] = 1;
	for(int m = 1; m <= k; ++m){
		auto tmp = P;
		for(auto par : P){
			lli idx = par.first + power(b,m)+1;
			tmp[idx] -= par.second;
			if(tmp[idx] < 0) tmp[idx] += mod;
		}
		P = tmp;
	}
	lli ans = 0;
	for(auto par : P){
		lli idx = n - par.first;
		if(idx < 0) break;
		ans += par.second * ncr(idx + k, k) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(int k = 10; k <= 15; ++k){
		ans += solve(power(10, k), k, k);
		if(ans >= mod) ans -= mod;
	}
	cout << (long long int)ans << "\n";
	return 0;
}