#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return primes;
}

const lli N = 1e16;
const int M = sqrt(N);
const auto primes = sieve(M);

unordered_set<lli> used;

lli g(lli p, int e){
	if(used.count(p)) return 0;
	if(e >= 2) return 0;
	return 1;
}

inline lli G(lli n){ //sum g(i, 1) , 1 <= i <= n
	return n;
}

lli f(lli n, int idx = 0){
	lli ans = G(n);
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p * p);
		if(!curr) break;
		int e = 1;
		while(curr >= 1){
			ans += (g(p, e + 1) - g(p, 1) * g(p, e)) * f(curr, i+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

lli C(int k, lli n){
	function<lli(lli, int, int)> dfs = [&](lli n, int pos, int cnt){
		if(cnt == k){
			return f(n);
		}else{
			lli ans = 0;
			for(int i = pos; i < primes.size(); ++i){
				lli p = primes[i];
				lli nxt = n / (p * p);
				if(nxt == 0) break;
				used.insert(p);
				ans += dfs(nxt, i+1, cnt+1);
				used.erase(p);
			}
			return ans;
		}
	};
	return dfs(n, 0, 0);
}

int main(){
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