#include <bits/stdc++.h>
using namespace std;

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

const int M = 1e6;
const auto primes = sieve(M);

int64_t power(int64_t a, int64_t b, int64_t m){
	a %= m;
	int64_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	int k = 1e9;
	int cnt = 0;
	int64_t sum = 0;
	for(int p : primes){
		if(p <= 5) continue;
		int x = power(10, k, p);
		if(x == 1){
			cnt++;
			sum += p;
			cout << cnt << ". " << p << "\n";
			if(cnt == 40) break;
		}
	}
	cout << sum << "\n";
	return 0;
}