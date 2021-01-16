#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1234567891;
const lli inv_4 = (mod + 1) / 4;

class TheBeautifulBoard{
	private:
	const int M = 1e5;
	vector<int> fact, inv, invfact;
	
	lli extract(int l, lli d, const vector<int> & expo, lli last){
		if(last % l != 0) return 0;
		last /= l;
		if(d/mod - last/mod > 0) return 0;
		lli ans = 1;
		for(int e : expo){
			if(e % l != 0) return 0;
			ans = ans * invfact[e/l] % mod;
		}
		last %= mod, d %= mod;
		for(lli i = last+1; i <= d; ++i){
			ans = ans * i % mod;
		}
		return ans;
	}
	
	public:
	TheBeautifulBoard(): fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1){
		for(int i = 2; i <= M; ++i){
			fact[i] = (lli)i * fact[i-1] % mod;
			inv[i] = mod - (lli)(mod / i) * inv[mod % i] % mod;
			invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
		}
	}
	
	int count(int n, vector<int> checkers){
		int sum = accumulate(checkers.begin(), checkers.end(), 0);
		if(sum > (lli)n*n) return 0;
		lli rem = (lli)n*n - sum;
		lli ans = extract(1, (lli)n*n, checkers, rem);
		if(n % 2 == 0){
			ans += 2*extract(4, (lli)n*n/4, checkers, rem) + extract(2, (lli)n*n/2, checkers, rem);
			ans %= mod;
		}else{
			for(int i = 0; i < checkers.size(); ++i){
				checkers[i]--;
				ans += 2*extract(4, ((lli)n*n-1)/4, checkers, rem) + extract(2, ((lli)n*n-1)/2, checkers, rem);
				ans %= mod;
				checkers[i]++;
			}
			if(rem > 0){
				ans += 2*extract(4, ((lli)n*n-1)/4, checkers, rem-1) + extract(2, ((lli)n*n-1)/2, checkers, rem-1);
				ans %= mod;
			}
		}
		ans = ans * inv_4 % mod;
		return ans;
	}
};