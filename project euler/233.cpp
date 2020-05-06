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

const int M = 5e6;
const lli lim = 1e11;
const auto primes = sieve(M);

vector<int> sieve2(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

int main(){
	vector<int> primes_1, primes_2;
	for(int p : primes){
		if(p % 4 == 1){
			primes_1.push_back(p);
		}else{
			primes_2.push_back(p);
		}
	}
	vector<lli> basic;
	int sz = primes_1.size();
	for(int i = 0; i < sz; ++i){
		int p = primes_1[i];
		for(int j = 0; j < sz; ++j){
			int q = primes_1[j];
			if(q == p) continue;
			if((lli)p*q*q > lim) break;
			for(int k = 0; k < sz; ++k){
				int r = primes_1[k];
				if(r == p || r == q) continue;
				if((lli)p*q*q*r*r*r > lim) break;
				basic.push_back((lli)p*q*q*r*r*r);
			}
		}
	}
	for(int i = 0; i < sz; ++i){
		int p = primes_1[i];
		if(2*log10l(p) > log10l(lim)) break;
		for(int j = 0; j < sz; ++j){
			int q = primes_1[j];
			if(q == p) continue;
			if(2*log10l(p) + 10*log10l(q) > log10l(lim)) break;
			basic.push_back((lli)p*p*q*q*q*q*q*q*q*q*q*q);
		}
	}
	for(int i = 0; i < sz; ++i){
		int p = primes_1[i];
		if(3*log10l(p) > log10l(lim)) break;
		for(int j = 0; j < sz; ++j){
			int q = primes_1[j];
			if(q == p) continue;
			if(3*log10l(p) + 7*log10l(q) > log10l(lim)) break;
			basic.push_back((lli)p*p*p*q*q*q*q*q*q*q);
		}
	}
	sort(basic.begin(), basic.end());
	
	int lim2 = lim / basic[0];
	const auto lp = sieve2(lim2);
	vector<lli> invalid, acum;
	for(int i = 1; i <= lim2; ++i){
		int n = i;
		bool test = true;
		while(n > 1){
			int p = lp[n];
			while(n % p == 0) n /= p;
			test &= binary_search(primes_2.begin(), primes_2.end(), p);
			if(!test) break;
		}
		if(test) invalid.push_back(i);
	}
	acum.push_back(invalid[0]);
	for(int i = 1; i < invalid.size(); ++i){
		acum.push_back(acum[i-1] + invalid[i]);
	}

	lli sum = 0;

	for(lli n : basic){
		lli upper = lim / n;
		int pos = upper_bound(invalid.begin(), invalid.end(), upper) - invalid.begin();
		assert(pos >= 1);
		sum += n * acum[pos-1];
	}

	cout << sum << "\n";

	return 0;
}