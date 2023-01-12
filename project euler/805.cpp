#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli m){
	a %= m;
	if(a < 0) a += m;
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const auto lp = lpSieve(1e8);

auto fact(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		f.emplace_back(p, a);
	}
	return f;
}

int phi(int n){
	int ans = n;
	for(auto[p, _] : fact(n)){
		ans -= ans/p;
	}
	return ans;
}

int multiplicativeOrder(int a, int m){
	a %= m;
	int order = phi(m);
	for(auto[p, e] : fact(order)){
		for(int i = e; i >= 1; --i){
			if(powerMod(a, order/p, m) != 1) break;
			order /= p;
		}
	}
	return order;
}

const int inf = 2e9;
const lli mod = 1e9 + 7;

int main(){
	int N = 200;
	lli sum = 0;
	for(int u = 1; u <= N; ++u){
		for(int v = 1; v <= N; ++v){
			int num = u*u*u, den = v*v*v;
			if(10*den - num > 0 && __gcd(u, v) == 1){
				pair<int, int> ans = {inf, inf};
				for(int a = 1; a <= 9; ++a){
					long double L = log10l(num) - log10l(den) - log10l(10 - num*1.0l/den) + log10l(a);
					if(L < 0){
						int x = a*den , y = 10*den - num;
						int g = __gcd(x, y);
						x /= g, y /= g;
						if(__gcd(10, y) == 1){
							int d = multiplicativeOrder(10, y);
							ans = min(ans, {d, a});
						}
					}
				}
				auto[d, a] = ans;
				if(d != inf){
					int r = num * powerMod(den, mod-2, mod) % mod;
					int n = (powerMod(10, d, mod) - 1) * powerMod(10 - r, mod-2, mod) % mod * a % mod;
					sum += n;
					if(sum >= mod) sum -= mod;
				}
			}
		}
	}
	cout << sum << "\n";
	return 0;
}