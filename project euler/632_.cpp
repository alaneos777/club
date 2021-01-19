#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

pair<vector<int>, vector<int>> sieve(int n){
	vector<int> primes, lp(n+1), mu(n+1), w(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			mu[i] = -1;
			w[i] = 1;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
			else{
				mu[d] = -mu[i];
				w[d] = w[i] + 1;
			}
		}
	}
	return {mu, w};
}

const lli N = 1e16;
const int M = sqrt(N);
vector<int> mu, w;
lli ncr[51][51];

lli C(int k, lli n){
	lli ans = 0;
	for(lli i = 1; i*i <= n; ++i){
		if(mu[i] == 0) continue;
		ans += mu[i] * ncr[w[i]][k] * (n / (i * i));
	}
	if(k & 1) ans = -ans;
	return ans;
}

int main(){
	for(int i = 0; i <= 50; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
		}
	}
	tie(mu, w) = sieve(M);
	lli ans = 1;
	for(int k = 0; ; ++k){
		lli Cnk = C(k, N);
		if(Cnk == 0) break;
		cout << Cnk << " ";
		ans = ans * (Cnk % mod) % mod;
	}
	cout << "\n" << ans << "\n";
	return 0;
}