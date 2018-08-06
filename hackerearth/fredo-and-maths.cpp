#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
 
vector<lli> primes;
 
void sieve(lli n){
	vector<bool> isPrime(n + 1, true);
	primes.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(isPrime[i]){
			primes.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					isPrime[j] = false;
				}
			}
		}
	}
}
 
lli phi(lli n){
	lli ans = n;
	for(lli & p : primes){
		if(p * p > n) break;
		if(n % p == 0){
			while(n % p == 0) n /= p;
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}
 
lli modPow(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}
 
lli tower(lli x, lli k, lli m){
	if(k == 0) return 1;
	if(m == 1) return 0;
	return modPow(x, tower(x, k - 1, phi(m)), m);
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	sieve(1e4);
	int t;
	lli x, k, m;
	cin >> t;
	while(t--){
		cin >> x >> k >> m;
		cout << tower(x, k, m) << "\n";
	}
	return 0;
}