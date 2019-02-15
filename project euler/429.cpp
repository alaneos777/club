#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 9;

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

const int N = 1e8;
vector<int> primes = sieve(N);

lli potInFactorial(lli n, lli p){
	lli ans = 0, div = n;
	while(div /= p) ans += div;
	return ans;
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	lli ans = 1;
	for(lli p : primes){
		int a = potInFactorial(N, p);
		ans = ans * (1 + powerMod(p, 2*a, mod)) % mod;
	}
	cout << ans << "\n";
	return 0;
}