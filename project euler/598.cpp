#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = double;
const ld eps = 1e-9;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true); is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

int pot(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

int main(){
	int N = 100;
	vector<ld> LOG(N+1);
	for(int i = 1; i <= N; ++i){
		LOG[i] = logl(i);
	}
	vector<int> primes = sieve(N), exponents;
	for(int p : primes){
		exponents.push_back(pot(N, p));
	}
	int sz = primes.size();
	vector<ld> ex[2], sides[2];
	for(int i = 0; i < sz; ++i){
		ex[i&1].push_back(exponents[i]);
	}
	lli ans = 0;
	function<void(int, int, ld)> gen = [&](int sd, int pos, ld acum){
		if(pos == ex[sd].size()){
			if(sd == 1){
				acum = -acum;
				sides[sd].push_back(acum);
			}else{
				ans += upper_bound(sides[1-sd].begin(), sides[1-sd].end(), acum + eps) - lower_bound(sides[1-sd].begin(), sides[1-sd].end(), acum - eps);
			}
		}else{
			int a = ex[sd][pos];
			for(int i = 0; i <= a; ++i){
				gen(sd, pos+1, acum + LOG[i+1] - LOG[a-i+1]);
			}
		}
	};
	gen(1, 0, 0);
	sort(sides[1].begin(), sides[1].end());
	gen(0, 0, 0);
	ans /= 2;
	cout << ans/2 << "\n";
	return 0;
}