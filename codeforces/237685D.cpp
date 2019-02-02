#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 998244353;

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, a, b;
	cin >> n >> a >> b;
	lli r = a * inv(b - a, mod) % mod;
	lli q = (b - a) * inv(b, mod) % mod;
	lli r_pw = r;
	vector<lli> s(n+1), p(n+1), g(n+1), f(n+1);
	s[1] = p[1] = g[1] = 1;
	for(int i = 2; i <= n; ++i){
		s[i] = (s[i-1] + r_pw) % mod;
		r_pw = r_pw * r % mod;
	}
	for(int i = 2; i <= n; ++i){
		p[i] = p[i-1] * s[i] % mod;
	}
	for(int i = 2; i <= n; ++i){
		g[i] = (g[i-1] * g[i-1] + 2) % mod;
	}
	for(int i = 1; i <= n-1; ++i){
		f[i] = p[n] * inv(p[i], mod) % mod * inv(p[n-i], mod) % mod * power(q, (lli)i * (n - i), mod) % mod;
	}
	lli ans = 0;
	for(int i = 1; i <= n-1; ++i){
		ans = (ans + f[i] * g[i] % mod) % mod;
	}
	cout << ans << "\n";
	return 0;
}