#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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
const auto mu = muSieve(N/3);

int main(){
	vector<lli> G = {0, 0, 0, 1, 0, 1, 1, 2, 1};
	while(G.size() < N+1){
		int n = G.size();
		G.push_back(G[n-2] + G[n-3] + G[n-4] - G[n-5] - G[n-6] - G[n-7] + G[n-9]);
	}
	partial_sum(G.begin(), G.end(), G.begin());
	lli ans = 0;
	for(int d = 1; 3*d <= N; ++d){
		ans += mu[d] * G[N/d];
	}
	cout << ans << "\n";
	return 0;
}