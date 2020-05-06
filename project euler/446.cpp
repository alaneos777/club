#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const int N = 1e7;

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

const auto primes = sieve(sqrt((lli)N*N + 2*N + 2) + 100);

const lli inv_9 = powerMod(9, mod - 2, mod);

int main(){
	vector<vector<lli>> acum(2, vector<lli>(N+1));
	vector<vector<lli>> r(2, vector<lli>(N+1, 1));
	for(int t = 0; t < 2; ++t){
		for(lli i = 1; i <= N; ++i){
			acum[t][i] = (t == 0 ? i*i - 2*i + 2 : i*i + 2*i + 2);
		}
		for(int p : primes){
			if(p != 2 && p % 4 != 1) continue;
			lli raiz = sqrtMod(p - 1, p);
			if(raiz == -1) continue;
			lli r0 = ((t == 0 ? 1 : p-1) + raiz) % p;
			lli r1 = ((t == 0 ? 1 : p-1) - raiz) % p; if(r1 < 0) r1 += p;
			vector<lli> roots = {r0};
			if(r0 != r1) roots.push_back(r1);
			for(lli root : roots){
				for(lli i = root; i <= N; i += p){
					if(i == 0) continue;
					lli term = 1;
					while(acum[t][i] % p == 0){
						acum[t][i] /= p;
						term = term * p % mod;
					}
					r[t][i] = r[t][i] * (1 + term) % mod;
				}
			}
		}
	}
	lli sum = 0;
	for(lli i = 1; i <= N; ++i){
		if(acum[0][i] > 1){
			r[0][i] = r[0][i] * (1 + acum[0][i]) % mod;
		}
		if(acum[1][i] > 1){
			r[1][i] = r[1][i] * (1 + acum[1][i]) % mod;
		}
		lli term = r[0][i] * r[1][i] % mod;
		if(i%2 == 0){
			term = term * inv_9 % mod * 5 % mod;
		}
		sum += (term - i * i % mod * i % mod * i % mod - 4) % mod;
		if(sum >= mod) sum -= mod;
		if(sum < 0) sum += mod;
	}
	cout << sum << "\n";
	return 0;
}