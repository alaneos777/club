#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const vector<int> constants = {114, 82, 50, 18, -16, -52};
const lli m = 87654321;
const lli phi_m = 58394976;

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
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	assert(abs(r0) == 1);
	return s0;
}

const lli lim = 1e18;

int main(){
	int p = phi_m;
	for(int d : {2, 3, 23, 53, 499}){
		while(p % d == 0) p /= d;
		int tmp = power(64, p, m);
		while(tmp != 1){
			tmp = power(tmp, d, m);
			p *= d;
		}
	}
	lli den = inverse(200, m);
	lli mod = m * p;
	__int128 c_1 = m * inverse(m, p) % mod;
	__int128 c_2 = p * inverse(p, m) % mod;
	lli ans = 0;
	for(int r = 0; r < 6; ++r){
		for(int k1 = 0; k1 < p; ++k1){
			lli k2 = (power(2, 6*k1 + r + 1, m) + constants[r]) * den % m;
			if(k2 < 0) k2 += m;
			lli k = (k1 * c_1 + k2 * c_2) % mod;
			lli n = 6*k + r;
			if(n <= lim){
				ans += (lim - n) / (6*mod) + 1;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}