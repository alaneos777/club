#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const lli N = 1e18;
const auto primes = sieve(cbrtl(N) + 100);

lli f(lli n, int idx = 0){
	lli ans = n;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p) / p;
		if(!curr) break;
		while(curr >= 1){
			ans += f(curr, i+1);
			curr /= p;
		}
	}
	return ans;
}

int main(){
	cout << f(N) << "\n";
	return 0;
}