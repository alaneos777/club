#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli sqrtMod(lli a, lli p){
	a %= p;
	if(a < 0) a += p;
	if(a == 0) return 0;
	if(powerMod(a, (p - 1) / 2, p) != 1) return -1;
	if(p % 4 == 3) return powerMod(a, (p + 1) / 4, p);
	lli s = p - 1;
	int r = 0;
	while((s & 1) == 0) ++r, s >>= 1;
	lli n = 2;
	while(powerMod(n, (p - 1) / 2, p) != p - 1) ++n;
	lli x = powerMod(a, (s + 1) / 2, p);
	lli b = powerMod(a, s, p);
	lli g = powerMod(n, s, p);
	while(true){
		lli t = b;
		int m = 0;
		for(; m < r; ++m){
			if(t == 1) break;
			t = t * t % p;
		}
		if(m == 0) return x;
		lli gs = powerMod(g, 1 << (r - m - 1), p);
		g = gs * gs % p;
		x = x * gs % p;
		b = b * g % p;
		r = m;
	}
}

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = sqrt(5e15);
const int limit = 5e7;
const auto primes = sieve(M);

int main(){
	vector<bool> is(limit+1, true);
	for(int p : primes){
		if(p % 4 != 1) continue;
		lli raiz = sqrtMod(p - 1, p);
		if(raiz == -1) continue;
		lli inv2 = (p + 1) / 2;
		lli r0 = (p-1 + raiz) * inv2 % p;
		lli r1 = (p-1 - raiz) * inv2 % p; if(r1 < 0) r1 += p;
		for(lli i = r0; i <= limit; i += p){
			if(i*i + (i+1)*(i+1) != p){
				is[i] = false;
			}
		}
		if(r1 != r0){
			for(lli i = r1; i <= limit; i += p){
				if(i*i + (i+1)*(i+1) != p){
					is[i] = false;
				}
			}
		}
	}
	int ans = 0;
	for(lli n = 1; n <= limit; ++n){
		if(is[n]){
			//cout << n << " " << n*n + (n+1)*(n+1) << "\n";
			ans++;
		}
	}
	cout << ans << "\n";
	return 0;
}