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
	if(a == 0) return 0;
	if(p == 2) return 1;
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

const int M = 3e7;
const int L = 500;
const auto primes = sieve(L);

/*
smallest z such that number of (x,y) with (6x-1)^2 + (6y-1)^2 = (6z-1)^2 + 1 and x <= y is over 100
(6z-1)^2 + 1 = 0 mod p
z = (1 +- i) / 6 mod p
*/

int main(){
	vector<lli> acum(M+1);
	vector<int> divs(M+1, 1);
	for(lli i = 1; i <= M; ++i){
		acum[i] = 36*i*i - 12*i + 2;
	}
	for(int p : primes){
		vector<int> roots;
		if(p == 2){
			roots = {0, 1};
		}else if(p%4 == 1){
			lli I = sqrtMod(p-1, p);
			int r0 = (1 + I) * powerMod(6, p-2, p) % p;
			int r1 = (1 - I) * powerMod(6, p-2, p) % p;
			if(r1 < 0) r1 += p;
			roots = {r0, r1};
		}
		for(int root : roots){
			for(int i = root; i <= M; i += p){
				if(i == 0) continue;
				int a = 0;
				while(acum[i] % p == 0){
					acum[i] /= p;
					a++;
				}
				if(p > 2) divs[i] *= a+1;
			}
		}
	}
	for(lli i = 1; i <= M; ++i){
		if(acum[i] > 1) continue;
		lli n = i*(3*i-1)/2;
		int ways = (divs[i]+7) / 8;
		if(ways > 100){
			cout << n << " -> " << ways << "\n";
			break;
		}
	}
	return 0;
}