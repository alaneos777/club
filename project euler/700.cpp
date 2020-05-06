#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

int main(){
	lli mod = 4503599627370517ll;
	lli a = 0;
	lli inc = 1504170715041707ll;
	lli inv = inverse(inc, mod);
	lli minimo = -1;
	lli sum = 0;
	while(true){
		a = (a + inc) % mod;
		if(minimo == -1 || a < minimo){
			minimo = a;
			cout << a << "\n";
			sum += a;
			if(a < (int)1.5e7) break;
		}
	}
	map<lli, lli> rem;
	for(lli i = 1; i < a; ++i){
		lli m = (__int128)i * inv % mod;
		rem[m] = i;
	}
	for(const auto & par : rem){
		if(par.second < minimo){
			sum += par.second;
			minimo = par.second;
			cout << par.second << "\n";
		}
	}
	cout << sum << "\n";
	return 0;
}