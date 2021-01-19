#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;
const lli mod = 1e9;

pair<vector<int>, vector<int>> sieve(int n){
	vector<int> primes, lp(n+1), phi(n+1), mu(n+1);
	phi[1] = mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
			phi[i] = i-1;
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p){
				phi[d] = phi[i] * p;
				break;
			}else{
				phi[d] = phi[i] * (p-1);
				mu[d] = -mu[i];
			}
		}
	}
	return {phi, mu};
}

const int N = 510510;
const lli M = 1e11;
const int limit = powl(M, 2.0/3.0);
vector<int> phi, mu;

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			if(mu[i]) divs[j].push_back(i);
		}
	}
	return divs;
}

vector<vector<int>> divs;
vector<lli> phiSmall;
unordered_map<int64_t, lli> phiBig;

lli PHI(int64_t n){
	if(n < phiSmall.size()) return phiSmall[n];
	if(phiBig.count(n)) return phiBig[n];
	lli ans = (lli)n*(n+1)/2;
	int64_t m = sqrtl(n);
	for(int64_t i = 2, l = n/m; i <= l; ++i){
		ans -= PHI(n/i);
	}
	for(int64_t i = 1; i < m; ++i){
		ans -= (n/i - n/(i+1)) * PHI(i);
	}
	return phiBig[n] = ans;
}

map<pair<int64_t, int64_t>, lli> mem;
lli S(int64_t n, int64_t m){
	if(n == 1) return PHI(m);
	if(mem.count({n, m})) return mem[{n, m}];
	lli ans = 0;
	for(int e : divs[n]){
		int64_t nxt1 = m/e;
		if(nxt1 == 0) break;
		lli term = 0;
		for(int d : divs[n/e]){
			int64_t nxt2 = nxt1/d;
			if(nxt2 == 0) break;
			term += ((lli)d * phi[n] / phi[d]) * S(d*e, nxt2);
		}
		if(mu[e] == 1){
			ans += term;
		}else if(mu[e] == -1){
			ans -= term;
		}
	}
	return mem[{n, m}] = ans;
}

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

int main(){
	tie(phi, mu) = sieve(max(N, limit));
	divs = divsSieve(N);
	phiSmall.resize(limit+1);
	for(int i = 1; i <= limit; ++i){
		phiSmall[i] = phi[i] + phiSmall[i-1];
	}
	lli ans = S(N, M);
	cout << ans << "\n";
	cout << ans%mod << "\n";
	return 0;
}