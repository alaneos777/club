#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return primes;
}

const int M = 200;
const lli N = 1e12;
const auto primes = sieve(M);

lli potFact(lli n, lli p){
	lli ans = 0;
	while(n /= p) ans += n;
	return ans;
}

lli f(lli n){
	lli m = sqrtl(n);
	lli ans = 0;
	for(lli i = 1; i <= m; ++i){
		ans += n/i;
	}
	return (2*ans - m*m) % mod;
}

int main(){
	vector<int> as;
	for(int p : primes){
		as.push_back(potFact(M, p));
	}
	int sz = as.size();
	vector<int> curr(sz);
	function<lli(int, lli)> dfs = [&](int pos, lli div){
		if(pos == sz){
			lli t = 1;
			int mu = 1;
			for(int i = 0; i < sz; ++i){
				int a = as[i] - curr[i];
				if(curr[i] == 1) mu = -mu;
				t = t * ((a+1) * (a+2) / 2) % mod;
			}
			lli ans = mu * f(N/div) * t % mod;
			if(ans < 0) ans += mod;
			return ans;
		}else{
			lli p = primes[pos];
			lli p_pow = 1;
			lli ans = 0;
			for(int i = 0; i <= 1; ++i){
				if(div*p_pow > N) break;
				ans += dfs(pos+1, div*p_pow);
				if(ans >= mod) ans -= mod;
				p_pow *= p;
				curr[pos] = i+1;
			}
			curr[pos] = 0;
			return ans;
		}
	};
	cout << dfs(0, 1) << "\n";
	return 0;
}