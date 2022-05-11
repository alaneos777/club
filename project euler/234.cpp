#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes; vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

const lli M = 999966663333ll;
const auto primes = sieve(2*sqrtl(M));

lli f(lli n, lli p, lli q){
	lli a = n/p, b = a/q;
	return a*(a+1)/2*p - b*(b+1)/2*p*q;
}

int main(){
	lli ans = 0;
	for(int i = 0; (lli)primes[i]*primes[i] <= M; ++i){
		lli p = primes[i], q = primes[i+1];
		lli L = p*p + 1, R = min(q*q - 1, M);
		ans += f(R, p, q) - f(L-1, p, q);
		ans += f(R, q, p) - f(L-1, q, p);
	}
	cout << ans << "\n";
	return 0;
}