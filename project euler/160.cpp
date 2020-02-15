#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli powerMod(lli a, lli b, lli mod){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli potInFactorial(lli n, lli p){
	lli ans = 0, div = n;
	while(div /= p) ans += div;
	return ans;
}

lli factmod(lli n, lli p, int s){
	lli ans = 1;
	lli ps = power(p, s);
	while(n > 1){
		lli q = n / ps, r = n % ps;
		ans = ans * (q % 2 == 1 && !(p == 2 && s >= 3) ? ps-1 : 1) % ps;
		for(lli i = 2; i <= r; ++i){
			if(i % p == 0) continue;
			ans = ans * i % ps;
		}
		n /= p;
	}
	return ans;
}

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0/r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

int main(){
	lli n;
	cin >> n;
	lli a = potInFactorial(n, 2);
	lli b = potInFactorial(n, 5);
	lli a0 = factmod(n, 2, 5) * powerMod(2, a-b, 32) % 32 * powerMod(inverse(5, 32), b, 32) % 32;
	lli a1 = factmod(n, 5, 5) * powerMod(inverse(2, 3125), b, 3125) % 3125;
	lli ans = (a0 * 3125 % 100000 * inverse(3125, 32) % 100000 + a1 * 32 % 100000 * inverse(32, 3125) % 100000) % 100000;
	cout << ans << "\n";
	/*
	a > b
	n!/(10^b) = P*2^(a-b)*5^(-b) mod 2^5
	n!/(10^b) = Q*2^(-b) mod 5^5
	*/
	return 0;
}