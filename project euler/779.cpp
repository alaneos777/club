#include <bits/stdc++.h>
using namespace std;
using ld = long double;

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return primes;
}

const int M = 1e6;
const auto primes = sieve(M);

int main(){
	ld ans = 0;
	ld prod = 1;
	for(int p : primes){
		prod *= (1 - 1.0l/p);
		ans += prod / powl(p-1, 3);
	}
	cout << fixed << setprecision(12) << ans << "\n";
	return 0;
}