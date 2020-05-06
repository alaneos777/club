#include <bits/stdc++.h>
using namespace std;
using lli =  long long int;

const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const lli inv_2 = power(2, mod - 2);
const lli inv_6 = power(6, mod - 2);

inline lli gauss(lli n, int p){
	n %= mod;
	if(p == 0) return n;
	if(p == 1) return n * (n + 1) % mod * inv_2 % mod;
	if(p == 2) return n * (n + 1) % mod * (2*n + 1) % mod * inv_6 % mod;
	if(p == 3){
		lli tmp = gauss(n, 1);
		return tmp * tmp % mod;
	}
	assert(0);
}

const lli limit = 235711131719ll;
const int M = pow(limit, 2.0/3.0);

vector<int> mu(M+1, 1), g(M+1, 1);

inline lli g_calc(lli p, int e){
	if(e == 1) return p * p % mod * (p - 1) % mod;
	if(e == 2) return mod - power(p, 5);
	return 0;
}

void sieve(){
	vector<int> cnt(M+1), acum(M+1), primes;
	vector<bool> isPrime(M+1, true);
	for(int i = 2; i <= M; ++i){
		if(isPrime[i]){ //case base: f(p)
			g[i] = g_calc(i, 1);
			mu[i] = -1;
			primes.push_back(i);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > M) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				g[d] = g[i / acum[i]] * g_calc(p, cnt[i] + 1) % mod;
				mu[d] = 0;
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				g[d] = g[i] * g_calc(p, 1) % mod;
				mu[d] = -mu[i];
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
}

vector<int> GSmall(M+1), USmall(M+1);
unordered_map<lli, int> GBig;

lli U(lli n){
	if(n <= M) return USmall[n];
	lli ans = 0;
	for(lli i = 1; i*i <= n; ++i){
		ans += mu[i] * power(i, 6) * gauss(n / (i*i), 3) %  mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

lli G(lli n){
	if(n <= M) return GSmall[n];
	if(GBig.count(n)) return GBig[n];
	lli ans = U(n);
	lli m = sqrt(n);
	for(lli i = 2, l = n/m; i <= l; ++i){
		ans -= i * i % mod * G(n/i) % mod;
		if(ans < 0) ans += mod;
	}
	for(lli i = 1; i < m; ++i){
		ans -= (gauss(n/i, 2) - gauss(n/(i+1), 2)) * G(i) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return GBig[n] = ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve();
	for(int i = 1; i <= M; ++i){
		GSmall[i] = GSmall[i-1] + g[i];
		if(GSmall[i] >= mod) GSmall[i] -= mod;
		USmall[i] = USmall[i-1] + power(i, 3) * mu[i] * mu[i];
		if(USmall[i] >= mod) USmall[i] -= mod;
	}
	int t;
	cin >> t;
	while(t--){
		lli n, m;
		cin >> n >> m;
		lli ans = 0;
		lli i = 1;
		while(i <= n && i <= m){
			lli ni = n / i, mi = m / i;
			lli u = min(n / ni, m / mi);
			ans += (G(u) - G(i-1)) * gauss(ni, 1) % mod * gauss(mi, 1) % mod;
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
			i = u + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}