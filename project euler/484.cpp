#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 5e15;

auto sieve(int n){
	vector<bool> is(n+1, true);
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const auto primes = sieve(sqrt(N) + 100);

inline lli power(lli a, lli n){
	lli ans = 1;
	while(n){
		if(n & 1) ans *= a;
		n >>= 1;
		a *= a;
	}
	return ans;
}

inline lli g(lli p, int e){ //g(n, 1) is multiplicative
	if(e % p == 0) return power(p, e);
	else return power(p, e-1);
}

inline lli G(lli n){ //sum g(i, 1) , 1 <= i <= n
	return n;
}

lli f(lli n, lli acum, int idx){
	lli ans = G(n) * acum;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(!curr) break;
		int e = 1;
		while(curr >= 1){
			lli acum2 = acum * (g(p, e + 1) - g(p, 1) * g(p, e));
			ans += f(curr, acum2, i+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

lli f(lli n){
	return f(n, 1, 0);
}

int main(){
	cout << f(N)-1 << "\n";
	return 0;
}