#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

const lli N = 1e16;
auto primes = sieve(sqrt(N));

lli v(lli p, int e){
	return e+1;
}

unordered_map<lli,lli> mem_V;
lli V(lli n){
	if(mem_V.count(n)) return mem_V[n];
	lli ans = 0;
	lli r = sqrt(n);
	for(lli i = 1; i <= r; ++i){
		ans += n/i;
	}
	return mem_V[n] = 2*ans - r*r;
}

lli f(lli p, int e){
	return 1ll<<e;
}

lli F(lli n, int idx = 0){
	lli ans = V(n);
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(curr == 0) break;
		int e = 2;
		lli u[65];
		u[0] = 1;
		u[1] = 0;
		while(curr >= 1){
			u[e] = f(p, e);
			for(int j = 0; j < e; ++j){
				u[e] -= u[j]*v(p, e-j);
			}
			ans += u[e] * F(curr, i+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

int main(){
	cout << F(N) << "\n";
	return 0;
}