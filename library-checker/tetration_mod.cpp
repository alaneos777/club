#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli mod){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < m) s0 += m;
	return s0;
}

auto fact(int n){
	vector<pair<int, int>> f;
	for(int p = 2; p*p <= n; ++p){
		int a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		if(a) f.emplace_back(p, a);
	}
	if(n > 1) f.emplace_back(n, 1);
	return f;
}

int phi(int n){
	int ans = n;
	for(auto[p, a]: fact(n)){
		ans -= ans/p;
	}
	return ans;
}

int f(int a, int n, int m){
	if(m == 1) return 0;
	if(n == 0) return 1;
	if(a == 0) return 1 - n%2;
	if(a == 1) return 1;
	int m1 = m, m2 = 1;
	while(true){
		int g = __gcd(a, m1);
		if(g == 1) break;
		m1 /= g;
		m2 *= g;
	}
	lli a1 = powerMod(a, f(a, n-1, phi(m1)), m1);
	lli a2 = 0;
	if((a == 2 && n >= 4) || (a == 3 && n >= 3) || (4 <= a && a <= 32 && n >= 2) || a >= 33){
		a2 = 0;
	}else{
		a2 = 1;
		for(int i = 1; i <= n; ++i){
			a2 = power(a, a2);
		}
		a2 %= m2;
	}
	return (a1 * m2 % m * inv(m2, m1) % m + a2 * m1 % m * inv(m1, m2) % m) % m;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int a, b, m;
		cin >> a >> b >> m;
		cout << f(a, b, m) << "\n";
	}
	return 0;
}