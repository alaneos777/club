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

const auto primes = sieve(1e6);

map<pair<lli, int>, lli> mem;
lli sum(lli n, int k){
	if(n <= 0) return 0;
	if(k <= -1) return 1;
	if(mem.count({n, k})) return mem[{n, k}];
	return mem[{n, k}] = sum(n, k-1) + sum(n/primes[k], k);
}

int main(){
	cout << sum(1e7, primes.size()-1) << "\n";
	cout << mem.size();
	return 0;
}