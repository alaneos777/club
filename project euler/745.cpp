#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

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

const lli N = 1e14;
const auto primes = sieve(sqrt(N) + 10);

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
	return power(p, 2 * (e / 2));
}

inline lli G(lli n){ //sum g(i, 1) , 1 <= i <= n
	return n;
}

lli f(lli n, int idx = 0){
	lli ans = G(n);
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(!curr) break;
		int e = 2;
		while(curr >= 1){
			ans += (g(p, e) - g(p, 1) * g(p, e - 1)) * f(curr, i+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

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

const lli mod = 1e9 + 7;

int main(){
	lli ans = f(N);
	cout << ans << "\n";
	cout << ans % mod << "\n";
	return 0;
}