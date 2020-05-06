#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto lpSieve(int n){
	vector<int> lp(n+1, 2);
	for(int i = 1; i <= n; i += 2) lp[i] = i;
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j){
					lp[j] = i;
				}
			}
		}
	}
	return lp;
}

const int M = 1e6;
const lli mod = 1e18;
const auto lp = lpSieve(M);

lli pot(lli n, lli p){
	lli ans = 0;
	while(n /= p) ans += n;
	return ans;
}

auto factorize(int x){
	vector<pair<int, int>> f;
	while(x > 1){
		int p = lp[x], e = 0;
		while(x % p == 0){
			x /= p;
			e++;
		}
		f.emplace_back(p, e);
	}
	return f;
}

int main(){
	uint64_t sum = 0;
	lli mult = 1234567890ll;
	lli n = 1;
	vector<int> fact(M+1);
	for(int i = 1; i <= M; ++i){
		auto curr_f = factorize(i);
		for(auto par : curr_f){
			int p, e;
			tie(p, e) = par;
			fact[p] += e;
			e = fact[p];
			lli target = mult * e;
			lli m = (__int128)target*(p-1)/p;
			while(pot(m*p, p) < target) m++;
			n = max(n, m*p);
		}
		if(i >= 10) sum = (sum + n) % mod;
	}
	cout << sum << "\n";
	return 0;
}