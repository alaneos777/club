#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int inverse(int a, int m){
	int r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	assert(abs(r0) == 1);
	return s0;
}

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

const int M = 3e5;
const auto primes = sieve(M);

int main(){
	int k = primes.size();

	vector<int> x(k);
	vector<bool> vis(k);
	for(int i = 0; i < k; ++i){
		x[i] = i+1;
		for(int j = 0; j < i; ++j){
			x[i] = (lli)inverse(primes[j], primes[i]) * (x[i] - x[j]) % primes[i];
			if(x[i] < 0){
				x[i] += primes[i];
			}
		}
	}

	for(int r = 0; r < k; ++r){
		int p = primes[r];
		int sum = 0;
		lli prod = 1;
		for(int i = 0; i < k; ++i){
			sum += prod * x[i] % p;
			if(sum >= p) sum -= p;
			if(sum == 0){
				vis[r] = true;
			}
			prod = prod * primes[i] % p;
		}
	}

	lli ans = 0;
	for(int i = 0; i < k; ++i){
		if(vis[i]){
			ans += primes[i];
		}
	}
	cout << ans << "\n";
	return 0;
}