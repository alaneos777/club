#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
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

lli Sqrt(lli n){
	lli r = sqrt(n);
	for(lli i = max(0ll, r-2); i <= r+2; ++i){
		if(i*i == n) return i;
	}
	return -1;
}

const int M = 1e6;
const auto primes = sieve(M);

int main(){
	int cnt = 0;
	for(int p : primes){
		// p = 3k² + 3k + 1
		// k = [-3 + sqrt(12p - 3))] / 6
		lli r = Sqrt(12*p - 3);
		if(r == -1) continue;
		r -= 3;
		if(r % 6) continue;
		cnt++;
	}
	cout << cnt << "\n";
	return 0;
}