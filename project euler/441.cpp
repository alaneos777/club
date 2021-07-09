#include <bits/stdc++.h>
using namespace std;
using ld = double;

auto muSieve(int n){
	vector<int> primes, mu(n+1);
	vector<bool> is(n+1, true);
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
			if(i % p == 0) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const int N = 1e7;
const auto mu = muSieve(N);

ld S(int n){
	vector<ld> H(n+1);
	for(int i = 1; i <= n; ++i){
		H[i] = H[i-1] + 1.0/i;
	}
	ld ans = 0;
	for(int d = 1; d <= (n-1)/2; ++d){
		if(mu[d] == 0) continue;
		ld term = 0;
		for(int p = 1; p <= (n-1)/(2*d); ++p){
			term += (1 + 1.0/(d*p)) * (H[n/d - p] - H[p]);
		}
		ans += term * mu[d] / d;
	}
	for(int d = 1; d <= n/2; ++d){
		if(mu[d] == 0) continue;
		ld term = 0;
		for(int p = 1; p <= n/(2*d); ++p){
			term += ((n+1)/(ld)d * (H[n/d] - H[n/d - p]) - p) / p;
		}
		ans += term * mu[d] / d;
	}
	for(int d = 1; d <= n-1; ++d){
		if(mu[d] == 0) continue;
		ld term = 0;
		for(int p = n/(2*d) + 1; p <= (n-1)/d; ++p){
			term += ((n+1)/(ld)d * (H[n/d] - H[p]) - n/d + p) / p;
		}
		ans += term * mu[d] / d;
	}
	return ans;
}

int main(){
	cout << fixed << setprecision(4) << S(N) << "\n";
	return 0;
}