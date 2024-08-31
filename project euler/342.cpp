#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using LLI = __int128_t;

const LLI inf = 1e30;

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(i%p == 0) break;
		}
	}
	return lp;
}

const lli N = -1 + 1e10;
const int M = powl(N, 2.0l/3.0l);
const auto lp = lpSieve(M);

auto getFact(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], a = 0;
		while(n%p == 0){
			n /= p;
			++a;
		}
		f.emplace_back(p, a);
	}
	return f;
}

LLI getDivs_3(int k){
	auto f = getFact(k);
	reverse(f.begin(), f.end());
	LLI ans = inf;
	function<void(LLI, LLI, LLI, int)> dfs = [&](LLI d, LLI phi_d, LLI e, int pos){
		if(pos == f.size()){
			if(phi_d == e){
				ans = min(ans, d);
			}
		}else{
			auto[p, a] = f[pos];
			LLI p_pow = 1;
			LLI phi_p_pow = 1;
			for(int i = 0; i <= 3*a; ++i){
				if(pos != 0 || i%3 == 2) dfs(d * p_pow, phi_d * phi_p_pow, e / p_pow, pos+1);
				p_pow *= p;
				if(i == 0) phi_p_pow *= p-1;
				else phi_p_pow *= p;
			}
		}
	};
	dfs(1, 1, (LLI)k*k*k, 0);
	return ans;
}

int main(){
	lli sum = 0;
	for(int k = 2; k <= M; k += 2){
		LLI n = getDivs_3(k);
		if(n != inf && n <= N){
			sum += (lli)n;
			cout << (lli)n << "\n";
		}
	}
	cout << sum << "\n";
	return 0;
}