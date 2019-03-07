#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli powerMod(lli a, lli b, lli m){
	a %= m;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

vector<int> sieve(int n){
	vector<int> isPrime(n+1, true), primes;
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const vector<int> primes = sieve(1e5);

lli phi(lli n){
	lli ans = n;
	for(lli p : primes){
		if(p*p > n) break;
		if(n % p == 0){
			while(n % p == 0) n /= p;
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

lli f(lli b, lli n, lli m){
	if(m == 1) return 0;
	if(n == 0) return 1;
	lli m1 = m, m2 = 1;
	while(true){
		lli g = gcd(b, m1);
		if(g == 1) break;
		m1 /= g;
		m2 *= g;
	}
	lli a1 = powerMod(b, f(b, n-1, phi(m1)), m1), a2 = 0;
	if(n <= 4){
		a2 = 1;
		for(lli i = 1; i <= n; ++i){
			a2 = power(b, a2);
		}
		a2 %= m2;
	}
	return (a1 * m2 % m * inv(m2, m1) % m + a2 * m1 % m * inv(m1, m2) % m) % m;
}

int main(){
	lli mod = 1475789056;
	lli ans = (63 + f(2, 7, mod) + 2 * f(2, 90, mod)) % mod;
	cout << ans << "\n";
	return 0;
}