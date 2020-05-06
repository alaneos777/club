#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const vector<lli> mods = {7, 11, 73, 101, 137};
const lli mod = 77777777;

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

lli crt(const vector<lli> & a, const vector<lli> & m){
	lli prod = 1, p, ans = 0;
	for(const lli & ni : m) prod *= ni;
	for(int i = 0; i < a.size(); ++i){
		p = prod / m[i];
		ans += (a[i] % m[i]) * inverse(p, m[i]) % prod * p % prod;
		while(ans >= prod) ans -= prod; while(ans < 0) ans += prod;
	}
	return ans;
}

lli calc(lli n, lli p){
	vector<vector<lli>> ncr(p+1, vector<lli>(p+1));
	ncr[0][0] = 1;
	for(int i = 1; i <= p; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % p;
		}
	}
	vector<lli> a(p+1);
	a[0] = 1;
	for(int r = 1; r <= p; ++r){
		for(int i = 1; i <= r; ++i){
			(a[r] += ncr[r][i] * a[r-i]) %= p;
		}
	}
	lli fact = 1;
	for(lli i = 1; i <= n; ++i){
		fact = fact * i % p;
		if(!fact) break;
	}
	lli ans = 0;
	lli pref = 1;
	while(pref){
		(ans += pref * a[(n-1) % (p-1) + 1]) %= p;
		pref = pref * n % p;
		n--;
	}
	return ((ans - fact) % p + p) % p;
}

int main(){
	const lli N = 1e9;
	vector<lli> a;
	for(lli p : mods){
		a.push_back(calc(N, p));
	}
	lli ans = crt(a, mods);
	cout << mod - ans << "\n";
	return 0;
}