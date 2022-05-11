#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	vector<int8_t> mu(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
			else mu[d] = -mu[i];
		}
	}
	return make_pair(mu, primes);
}

const lli N = lli(1e16) - 1;
const auto[mu, primes] = sieve(sqrtl(N));

lli F(lli n){
	lli ans = 0;
	for(lli k = 1; k*k <= n; k += 2){
		ans += mu[k] * ((n / (k*k) + 3) / 4);
	}
	return ans;
}

int main(){
	clock_t start = clock();

	lli ans = F(N);
	for(lli p : primes){
		lli n = N / (p*p);
		if(n == 0) break;
		if(p%4 == 3) ans += F(n);
	}
	clock_t end = clock();
	cout << ans << "\n";
	cout << double(end - start) / CLOCKS_PER_SEC << "\n";
	return 0;
}