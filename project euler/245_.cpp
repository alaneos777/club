#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

auto sieve2(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return is;
}

const lli N = 2e11;
const lli M = pow(N, 2.0 / 3.0);

int main(){
	lli ans = 0;
	auto is = sieve2(M);

	auto primes = sieve(sqrt(N));
	int sz = primes.size();
	for(int i = 1; i < sz; ++i){
		lli p = primes[i];
		for(lli h = 2; ; h += 2){
			lli den = p*(1-h) + h*(p-1);
			if(den <= 0) break;
			lli num = h*(p-1) + 1;
			if(num % den == 0){
				lli q = num / den;
				if(q > p && q <= M && is[q]){
					if(p*q <= N) ans += p*q;
				}
			}
		}
	}

	primes = sieve(sqrt(N)/3);
	sz = primes.size();
	for(int i = 1; i < sz; ++i){
		lli p = primes[i];
		for(int j = i+1; j < sz; ++j){
			lli q = primes[j];
			if(p*q*q > N) break;
			for(lli h = 2; ; h += 2){
				lli den = p*q*(1-h) + h*(p-1)*(q-1);
				if(den <= 0) break;
				lli num = h*(p-1)*(q-1) + 1;
				if(num % den == 0){
					lli r = num / den;
					if(r > q && r <= M && is[r]){
						if(p*q*r <= N) ans += p*q*r;
					}
				}
			}
		}
	}
	
	primes = sieve(sqrt(N)/3/5);
	sz = primes.size();
	for(int i = 1; i < sz; ++i){
		lli p = primes[i];
		for(int j = i+1; j < sz; ++j){
			lli q = primes[j];
			if(p*q > N) break;
			for(int k = j+1; k < sz; ++k){
				lli r = primes[k];
				if(p*q*r*r > N) break;
				for(lli h = 2; ; h += 2){
					lli den = p*q*r*(1-h) + h*(p-1)*(q-1)*(r-1);
					if(den <= 0) break;
					lli num = h*(p-1)*(q-1)*(r-1) + 1;
					if(num % den == 0){
						lli s = num / den;
						if(s > r && s <= M && is[s]){
							if(p*q*r*s <= N) ans += p*q*r*s;
						}
					}
				}
			}
		}
	}

	primes = sieve(sqrt(N)/3/5/7);
	sz = primes.size();
	for(int i = 1; i < sz; ++i){
		lli p = primes[i];
		for(int j = i+1; j < sz; ++j){
			lli q = primes[j];
			if(p*q > N) break;
			for(int k = j+1; k < sz; ++k){
				lli r = primes[k];
				if(p*q*r > N) break;
				for(int l = k+1; l < sz; ++l){
					lli s = primes[l];
					if(p*q*r*s*s > N) break;
					for(lli h = 2; ; h += 2){
						lli den = p*q*r*s*(1-h) + h*(p-1)*(q-1)*(r-1)*(s-1);
						if(den <= 0) break;
						lli num = h*(p-1)*(q-1)*(r-1)*(s-1) + 1;
						if(num % den == 0){
							lli t = num / den;
							if(t > s && t <= M && is[t]){
								if(p*q*r*s*t <= N) ans += p*q*r*s*t;
							}
						}
					}
				}
			}
		}
	}

	cout << ans << "\n";
	return 0;
}