#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i])
			primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = 5e6;
const lli mod = 1e8 + 7;
const lli inv2 = 5e7 + 4;
vector<int> primes = sieve(M);

lli pot(lli n, lli p){
	lli ans = 0, den = p;
	while(den <= n){
		lli k = (n + 1) / den;
		ans += k * (2*(n + 1)%mod - den*(k + 1)%mod) % mod * inv2 % mod;
		ans %= mod;
		den *= p;
	}
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n && n != 0){
		lli ans = 1;
		for(int p : primes){
			if(p > n) break;
			lli a = pot(n, p);
			ans = ans * (a + 1) % mod;
		}
		cout << ans << "\n";
	}
	return 0;
}