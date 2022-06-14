#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, 1);
	is[0] = is[1] = false;
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

const auto primes = sieve(2e7);

int main(){
	int N = 800800;
	lli ans = 0;
	for(int i = 0, j = primes.size()-1; i < j && i < primes.size()-1; ++i){
		// p^q * q^p <= N^N
		// greatest q prime such that q*log(p) + p*log(q) <= N*log(N)
		int p = primes[i];
		while(i < j && primes[j]*log(p) + p*log(primes[j]) > N*log(N)) j--;
		ans += j-i;
	}
	cout << ans << "\n";
	return 0;
}