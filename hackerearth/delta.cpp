#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

auto sieve(int n){
	vector<int> primes, f(n+1);
	vector<bool> is(n+1, true);
	f[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			f[i] = 1 - (lli)i*i % mod;
			if(f[i] < 0) f[i] += mod;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0){
				f[d] = f[i];
				break;
			}else{
				f[d] = (lli)f[i] * f[p] % mod;
			}
		}
	}
	return f;
}

const lli inv2 = (mod + 1) / 2;

lli gauss(lli n){
	return n * (n + 1) % mod * inv2 % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	auto f = sieve(n);
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += f[i] * gauss(n/i) % mod * gauss(n/i) % mod;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}