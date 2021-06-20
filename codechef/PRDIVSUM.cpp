#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const int L = 1e7;
vector<int> sq_small(L+1);
map<lli, lli> sq_big;
lli cnt_sq_free(lli n){
	if(n < sq_small.size()) return sq_small[n];
	if(sq_big.count(n)) return sq_big[n];
	lli ans = 0;
	for(lli i = 1; i*i <= n; ++i){
		ans += mu[i] * (n / (i*i));
	}
	return sq_big[n] = ans;
}

lli sum_sq_free(lli l, lli r, lli m){
	lli ans = 0;
	lli i = l;
	while(i <= r){
		lli u = m / (m / i);
		ans += m/i * (cnt_sq_free(min(u, r)) - cnt_sq_free(i-1));
		i = u+1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(L);
	for(int i = 1; i <= L; ++i){
		sq_small[i] = sq_small[i-1] + mu[i]*mu[i];
	}
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		lli ans = 0;
		for(lli s = 1; s*s <= n; ++s){
			ans += (2*s-1) * cnt_sq_free(n / (s * (2*s-1)));
			ans -= s * cnt_sq_free(n / (s*s));
			ans += sum_sq_free(n / (s * (2*s-1)) + 1, n / (s*s), n/s);
		}
		cout << ans << "\n";
	}
	return 0;
}