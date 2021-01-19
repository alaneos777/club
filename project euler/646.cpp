#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;
const lli mod = 1e9 + 7;

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

int potInFact(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

int main(){
	int n = 70, L = 20, R = 60;
	auto primes = sieve(n);
	bool side = 0;
	vector<pair<int, int>> fact[2];
	for(int p : primes){
		int a = potInFact(n, p);
		fact[side].emplace_back(p, a);
		side ^= 1;
	}

	vector<pair<ld, int>> lists[2];
	function<void(int, int, ld, lli)> combine = [&](int sd, int pos, ld div, lli acum){
		if(fact[sd].size() == pos){
			lists[sd].emplace_back(div, acum);
		}else{
			int p, a;
			tie(p, a) = fact[sd][pos];
			lli p_pow = 1;
			for(int i = 0; i <= a; ++i){
				combine(sd, pos+1, div + i*log10l(p), acum * p_pow % mod);
				p_pow = p_pow * (mod-p) % mod;
			}
		}
	};
	combine(0, 0, 0, 1);
	sort(lists[0].begin(), lists[0].end());
	combine(1, 0, 0, 1);
	sort(lists[1].begin(), lists[1].end());

	if(lists[0].size() > lists[1].size()){
		swap(lists[0], lists[1]);
	}

	int sz_lhs = lists[0].size();
	int sz_rhs = lists[1].size();
	vector<int> sums_rhs(sz_rhs);
	sums_rhs[0] = lists[1][0].second;
	for(int i = 1; i < sz_rhs; ++i){
		sums_rhs[i] = sums_rhs[i-1] + lists[1][i].second;
		if(sums_rhs[i] >= mod) sums_rhs[i] -= mod;
	}

	int ans = 0;
	for(auto par : lists[0]){
		ld div; int f;
		tie(div, f) = par;
		// div + x <= R ---> max idx such that lists[1][idx].first <= R-div
		int lo = 0, hi = sz_rhs-1, idx1 = -1, idx2 = -1;
		while(lo <= hi){
			int m = (lo + hi) / 2;
			if(lists[1][m].first <= R-div){
				idx2 = m;
				lo = m+1;
			}else{
				hi = m-1;
			}
		}
		// L <= div + x ---> min idx such that lists[1][idx].first >= L-div
		lo = 0, hi = sz_rhs-1;
		while(lo <= hi){
			int m = (lo + hi) / 2;
			if(lists[1][m].first >= L-div){
				idx1 = m;
				hi = m-1;
			}else{
				lo = m+1;
			}
		}
		if(idx1 != -1 && idx2 != -1){
			ans += (lli)f * (sums_rhs[idx2] - (idx1 ? sums_rhs[idx1-1] : 0)) % mod;
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
		}
	}

	cout << ans << "\n";

	return 0;
}