#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

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
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0){
				break;
			}else{
				mu[d] = -mu[i];
			}
		}
	}
	return mu;
}

const int M = 1e7;
const auto mu = muSieve(M);

lli cnt(lli a, lli b){
	lli ans = 0;
	for(int i = 1; i <= a && i <= b; ++i){
		ans += mu[i] * (a / i) * (b / i);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	lli ans = cnt(b, d) - cnt(a-1, d) - cnt(b, c-1) + cnt(a-1, c-1);
	cout << ans << "\n";
	return 0;
}