#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	isPrime[0] = isPrime[1] = false;
	vector<int> sumPrimes(n+1);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	for(int i = 1; i <= n; ++i){
		sumPrimes[i] = sumPrimes[i-1] + isPrime[i];
	}
	return sumPrimes;
}

const int M = 7.1e8;
const auto sumPrimes = sieve(M);

lli s(int n){
	lli ans = 0;
	for(int k = 1; k <= 1 && k <= n; ++k){
		ans += sumPrimes[n];
	}
	for(int k = 2; k <= 2 && k <= n; ++k){
		ans += n/2 - 1;
		ans += max(0, sumPrimes[n-2] - 1);
	}
	if(n >= 3){
		lli N = n/2 - 2;
		if(n % 2 == 0){
			ans += N*N;
		}else{
			ans += N*(N+1);
		}
	}
	return ans;
}

int main(){
	vector<int> f = {0, 1};
	while(f.size() <= 44){
		f.push_back(f[f.size()-1] + f[f.size()-2]);
	}
	lli ans = 0;
	for(int k = 3; k <= 44; ++k){
		ans += s(f[k]);
	}
	cout << ans << "\n";
	return 0;
}