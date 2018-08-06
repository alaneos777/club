#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<int> primes;
vector<bool> isPrime;
void sieve(int n){
	isPrime.assign(n+1, true);
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
}

lli phi(lli n){
	lli ans = n;
	for(lli p : primes){
		if(p * p > n) break;
		if(n % p == 0){
			while(n % p == 0) n /= p;
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < m) s0 += m;
	return s0;
}

lli expBin(lli a, lli b, lli m){
	a %= m;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

lli exp(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli f(lli n, lli m){
	if(m == 1) return 0;
	if(n == 1) return 1;
	lli m1 = m, m2 = 1;
	while(true){
		lli g = gcd(n, m1);
		if(g == 1) break;
		m1 /= g;
		m2 *= g;
	}
	//all prime factors of m2 are also factors of n now
	lli a1 = expBin(n, f(n - 1, phi(m1)), m1);
	lli a2 = 0;
	if(n <= 4){
		a2 = 1;
		for(lli i = 1; i < n; ++i){
			a2 = exp(i + 1, a2);
		}
		a2 %= m2;
	}
	return (a1 * m2 % m * inv(m2, m1) % m + a2 * m1 % m * inv(m1, m2) % m) % m;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	sieve(31630);
	lli n, m;
	cin >> n >> m;
	cout << f(n, m) << "\n";
	return 0;
}