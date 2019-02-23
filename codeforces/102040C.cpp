#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e7 + 7;
const lli inv2 = 5e6 + 4;

lli potInFact(lli n, lli p){
	lli div = n, pot = 0;
	while(div /= p) pot += div;
	return pot;
}

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

const vector<int> primes = sieve(1000000);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n && n != 0){
		lli ans = 1;
		for(lli p : primes){
			if(p > n) break;
			lli a = potInFact(n, p);
			ans = ans * (a + 1) % mod * (a + 2) % mod * inv2 % mod;
		}
		cout << ans << "\n";
	}
	return 0;
}