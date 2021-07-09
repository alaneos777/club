// https://www.emis.de/journals/INTEGERS/papers/g14/g14.pdf
#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const auto primes = sieve(5000-1);

int main(){
	/*lli ans = 0;
	for(int i = 0; i < primes.size()-2; ++i){
		for(int j = i+1; j < primes.size()-1; ++j){
			for(int k = j+1; k < primes.size(); ++k){
				lli p = primes[i];
				lli q = primes[j];
				lli r = primes[k];
				ans += 2*p*q*r - p*q - p*r - q*r;
			}
		}
	}
	cout << ans << "\n";*/
	lli p1 = 0, p2 = 0, p3 = 0;
	for(lli p : primes){
		p1 += p;
		p2 += p*p;
		p3 += p*p*p;
	}
	lli ans = (p1*p1*p1 - 3*p1*p2 + 2*p3)/3 - (p1*p1 - p2)/2 * (primes.size()-2);
	cout << ans << "\n";
	return 0;
}