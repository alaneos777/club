#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = __int128;

const lli mod = 1e16;

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

const auto primes = sieve(190);

int main(){
	int sz1 = primes.size() / 2;
	int sz2 = primes.size() - sz1;
	ld raiz = 0;
	for(int p : primes){
		raiz += 0.5l * logl(p);
	}
	vector<pair<ld, int>> rhs;
	for(int i = 0; i < (1<<sz2); ++i){
		ld sum = 0;
		for(int j = 0; j < sz2; ++j){
			if(i & (1 << j)){
				sum += logl(primes[sz1 + j]);
			}
		}
		rhs.emplace_back(sum, i);
	}
	sort(rhs.begin(), rhs.end());
	tuple<ld, int, int> ans = {0, 0, 0};
	for(int i = 0; i < (1<<sz1); ++i){
		ld sum = 0;
		for(int j = 0; j < sz1; ++j){
			if(i & (1 << j)){
				sum += logl(primes[j]);
			}
		}
		int pos = upper_bound(rhs.begin(), rhs.end(), make_pair(raiz - sum, 0)) - rhs.begin();
		pos--;
		if(pos >= 0 && pos < rhs.size()){
			ans = max(ans, {sum + rhs[pos].first, i, rhs[pos].second});
		}
	}
	ld sum_min; int mask_left, mask_right;
	tie(sum_min, mask_left, mask_right) = ans;
	lli psr = 1;
	for(int i = 0; i < sz1; ++i){
		if(mask_left & (1 << i)){
			psr = psr * primes[i] % mod;
		}
	}
	for(int i = 0; i < sz2; ++i){
		if(mask_right & (1 << i)){
			psr = psr * primes[sz1 + i] % mod;
		}
	}
	cout << (int64_t)psr << "\n";
	return 0;
}