#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

pair<vector<int>, vector<int>> sieve(int n){
	vector<int> primes, lp(n+1), mu(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
			}
		}
	}
	return {primes, mu};
}

const lli N = 1e8;
const int M = sqrt(N);
vector<int> primes, mu;

lli sqfree(lli n){
	lli ans = 0;
	for(lli i = 1; i * i <= n; ++i){
		ans += mu[i] * (n / (i * i));
	}
	return ans;
}

int main(){
	tie(primes, mu) = sieve(M);
	function<lli(lli, lli, int, int)> dfs = [&](lli n, lli acum, int pos, int len){
		if(pos == len){
			lli ans = sqfree(n * acum);
			return ans;
		}else{
			lli ans = 0;
			for(lli p : primes){
				lli prod = p * p;
				lli m = n / prod;
				if(m == 0) break;
				while(m){
					ans += dfs(m, acum * prod, pos+1, len);
					m /= p;
					prod *= p;
				}
			}
			return ans;
		}
	};
	cout << dfs(N, 1, 0, 1);
	return 0;
}