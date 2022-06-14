#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 993353399;
using vi = vector<pair<lli, int>>;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli getPhi(const vi& fact){
	lli ans = 1;
	for(auto[p, a] : fact){
		if(a) ans *= power(p, a) - power(p, a-1);
	}
	return ans;
}

void getDivs(const vi& fact, function<void(lli, const vi&, const vi&)> go){
	vi acum_fact(fact.size());
	vi comp_fact(fact.size());
	function<void(int, lli)> dfs = [&](int pos, lli div){
		if(pos == fact.size()){
			go(div, acum_fact, comp_fact);
		}else{
			auto[p, a] = fact[pos];
			lli p_pow = 1;
			for(int i = 0; i <= a; ++i){
				acum_fact[pos] = {p, i};
				comp_fact[pos] = {p, a-i};
				dfs(pos+1, div*p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1);
}

vi join(const vi& A, const vi& B){
	map<lli, int> C;
	for(auto[p, a] : A){
		C[p] += a;
	}
	for(auto[p, a] : B){
		C[p] += a;
	}
	vi ans(C.size());
	for(auto[p, a] : C){
		ans.emplace_back(p, a);
	}
	return ans;
}

int main(){
	lli L = 1e16, R = L+1e6;
	auto primes = sieve(sqrtl(R));
	vector<lli> rem(R - (L-1) + 1);
	iota(rem.begin(), rem.end(), L-1);
	vector<vi> facts(R-(L-1)+1);
	for(int p : primes){
		// L-1 <= p*k <= R
		// ceil((L-1)/p) <= k <= floor(R/p)
		for(lli k = ((L-1)+p-1)/p; k <= R/p; ++k){
			int idx = k*p - (L-1);
			int a = 0;
			while(rem[idx]%p == 0){
				rem[idx] /= p;
				a++;
			}
			facts[idx].emplace_back(p, a);
		}
	}
	for(lli i = L-1; i <= R; ++i){
		int idx = i - (L-1);
		if(rem[idx] > 1){
			facts[idx].emplace_back(rem[idx], 1);
			rem[idx] = 1;
		}
	}
	lli ans = 0;
	for(lli p = L; p <= R; ++p){
		int idx = p - (L-1);
		if(!(facts[idx].size() == 1 && facts[idx][0].second == 1)) continue;
		lli f = 0;
		getDivs(facts[idx-1], [&](lli u, const vi& fact_u, const vi& comp_fact_u){
			lli term = 0;
			getDivs(fact_u, [&](lli d, const vi& fact_d, const vi& comp_fact_d){
				term += (d % mod) * (getPhi(join(comp_fact_d, comp_fact_u)) % mod) % mod;
				if(term >= mod) term -= mod;
			});
			f += term*term % mod * (getPhi(comp_fact_u) % mod) % mod;
			if(f >= mod) f -= mod;
		});
		ans += (f + ((p-1)%mod) * ((p-1)%mod)) % mod;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}