#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 2.5e13;
const long double phi = (1 + sqrtl(5)) / 2;

vector<int> primes, mu;
void sieve(int n){
	mu.resize(n+1);
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
			else mu[d] = -mu[i];
		}
	}
}

const int L = min(1e8, pow(N, 2.0/3.0));
vector<int> sq_small(L+1);
map<lli, lli> sq_big;
lli sq(lli n){
	if(n < sq_small.size()) return sq_small[n];
	if(sq_big.count(n)) return sq_big[n];
	lli ans = 0;
	for(lli i = 1; i*i <= n; ++i){
		ans += mu[i] * (n / (i*i));
	}
	return sq_big[n] = ans;
}

int main(){
	sieve(max((int)sqrtl(N), L));
	for(int i = 1; i <= L; ++i){
		sq_small[i] = sq_small[i-1] + mu[i]*mu[i];
	}
	lli ans = 0;
	for(lli x = 1; 3*x*x <= N; ++x){
		lli y = x;
		lli lim = ceill(phi * x) - 1;
		while(y <= lim){
			lli k = N / (x*x + x*y + y*y);
			if(k == 0) break;
			lli u = (sqrtl(4 * (N/k) - 3*x*x) - x) / 2;
			ans += (min(u, lim) - (y-1)) * sq(k);
			y = u+1;
		}
	}
	cout << ans << "\n";
	return 0;
}