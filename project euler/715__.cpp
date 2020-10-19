#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli mod = 1e9 + 7;
const lli inv2 = (mod + 1) / 2;
const lli N = 1e12;
const int M = pow(N, 2.0 / 3.0);

inline lli P3(lli n){
	n %= mod;
	lli tmp = n * (n + 1) % mod * inv2 % mod;
	return tmp * tmp % mod;
}

inline lli x4(lli n){
	if((n & 3) == 1) return 1;
	else if((n & 3) == 3) return -1;
	else return 0;
}

inline lli X4(lli n){
	if((n & 3) == 1 || (n & 3) == 2) return 1;
	else return 0;
}

vector<int> sieve(int n, function<lli(int, int)> g){
	vector<int> f(n+1, 1);
	vector<int> cnt(n+1), acum(n+1), primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			f[i] = g(i, 1);
			primes.push_back(i);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				f[d] = f[i / acum[i]] * g(p, cnt[i] + 1) % mod;
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				f[d] = f[i] * g(p, 1) % mod;
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return f;
}

vector<int> G_small(M+1);
map<lli, lli> G_big;
lli G(lli n){
	if(n <= M) return G_small[n];
	if(G_big.count(n)) return G_big[n];
	lli ans = P3(n);
	int m = sqrt(n), l = n / m;
	for(int i = 2; i <= l; ++i){
		ans -= G(n / i) * x4(i);
		if(ans < 0) ans += mod;
		if(ans >= mod) ans -= mod;
	}
	for(int i = 1; i < m; ++i){
		ans -= (X4(n/i) - X4(n/(i+1))) * G(i) % mod;
		if(ans < 0) ans += mod;
		if(ans >= mod) ans -= mod;
	}
	return G_big[n] = ans;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	auto g_eval = sieve(M, [](lli p, int a){
		lli ans = power(p, 3*a);
		if(p >= 3){
			if((p & 3) == 3){
				ans += power(p, 3*a - 3);
			}else{
				ans -= power(p, 3*a - 3);
			}
		}
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		return ans;
	});
	for(int i = 1; i <= M; ++i){
		G_small[i] = G_small[i-1] + g_eval[i];
		if(G_small[i] >= mod) G_small[i] -= mod;
	}
	cout << G(N) << "\n";
	return 0;
}