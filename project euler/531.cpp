#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli extendedGcd(lli a, lli b, lli & s, lli & t){
	lli q, r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti;
	while(r1){
		q = r0 / r1;
		ri = r0 % r1, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
		ti = t0 - t1 * q, t0 = t1, t1 = ti;
	} 
	s = s0, t = t0;
	return r0;
}

lli crt(const vector<lli> & a, const vector<lli> & m){
	lli a0 = a[0] % m[0], m0 = m[0], a1, m1, s, t, d, M;
	for(int i = 1; i < a.size(); ++i){
		a1 = a[i] % m[i], m1 = m[i];
		d = extendedGcd(m0, m1, s, t);
		if((a0 - a1) % d != 0) return 0;
		M = m0 * (m1 / d);
		a0 = a0 * t % M * (m1 / d) % M + a1 * s % M * (m0 / d) % M;
		while(a0 >= M) a0 -= M; while(a0 < 0) a0 += M;
		m0 = M;
	}
	while(a0 >= m0) a0 -= m0; while(a0 < 0) a0 += m0;
	return a0;
}

auto phiSieve(int n){
	vector<int> phi(n+1);
	iota(phi.begin(), phi.end(), 0);
	for(int i = 2; i <= n; ++i){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
	return phi;
}

const auto phi = phiSieve(int(1.5e7));

int main(){
	lli ans = 0;
	for(int n = 1000000; n < 1005000; ++n){
		for(int m = n+1; m < 1005000; ++m){
			ans += crt({phi[n], phi[m]}, {n, m});
		}
	}
	cout << ans << "\n";
	return 0;
}