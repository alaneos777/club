#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

auto generalSieve(int n, function<lli(int, int)> g){
	vector<lli> f(n+1, 1);
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
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	auto g = generalSieve(n, [&](int p, int a){
		lli pk = power(p, k);
		lli ans = power(pk, a) - power(pk, a-1);
		if(ans < 0) ans += mod;
		return ans;
	});
	partial_sum(g.begin(), g.end(), g.begin());
	lli ans = 0;
	int i = 1;
	while(i <= n){
		int ni = n/i, u = n/ni;
		ans += (lli)ni*ni % mod * (g[u] - g[i-1]) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		i = u+1;
	}
	cout << ans << "\n";
	return 0;
}