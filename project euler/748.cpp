#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using comp = complex<lli>;
const lli mod = 1e9;

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
	return lp;
}

const lli N = 1e16;
const auto lp = sieve(sqrtl(N) + 1);

comp power(comp a, lli b){
	comp ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

comp sq2(lli p){
	assert(p >= 3 && p % 4 == 1);
	lli z;
	for(lli a = 2; a < p-1; ++a){
		if(powerMod(a, (p-1)/2, p) == p-1){
			z = powerMod(a, (p-1)/4, p);
			break;
		}
	}
	lli w0 = p, w1 = 0, z0 = z, z1 = 1;
	while(z0 || z1){
		lli n = z0*z0 + z1*z1;
		lli u0 = (w0*z0 + w1*z1) / n;
		lli u1 = (w1*z0 - w0*z1) / n;
		lli r0 = w0 - z0*u0 + z1*u1;
		lli r1 = w1 - z0*u1 - z1*u0;
		w0 = z0, w1 = z1, z0 = r0, z1 = r1;
	}
	return {lli(abs(w0)), lli(abs(w1))};
}

comp sq2_dp[(int)sqrtl(N)/4 + 20];

set<pair<lli, lli>> r2(lli n){
	if(n == 0) return {{0, 0}};
	set<pair<lli, lli>> s;
	vector<vector<comp>> lists;
	map<int, int> fact;
	while(n > 1){
		int p = lp[n], a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		fact[p] = 2*a;
	}
	fact[13]++;
	for(const auto & par : fact){
		lli p; int e;
		tie(p, e) = par;
		if(e == 0) continue;
		if(p % 4 == 3 && e % 2 == 1) return {};
	}
	for(const auto & par : fact){
		lli p; int e;
		tie(p, e) = par;
		if(e == 0) continue;
		vector<comp> list;
		if(p == 2){
			list.push_back(power({1, 1}, e));
		}else if(p % 4 == 3){
			list.push_back(power({p, 0}, e/2));
		}else{
			comp base_p = sq2_dp[p/4];
			for(int i = 0; i <= e; ++i){
				list.push_back(power(base_p, i) * conj(power(base_p, e-i)));
			}
		}
		lists.push_back(list);
	}
	function<void(int, comp)> rec = [&](int idx, comp acum){
		if(idx == lists.size()){
			lli a = abs(acum.real());
			lli b = abs(acum.imag());
			if(a > b) swap(a, b);
			if(__gcd(a, b) == 1) s.emplace(a, b);
		}else{
			for(int i = 0; i < lists[idx].size(); ++i){
				rec(idx + 1, acum * lists[idx][i]);
			}
		}
	};
	rec(0, 1);
	return s;
}

int main(){
	for(lli p = 5; p*p <= N; p += 4){
		if(lp[p] == p){
			sq2_dp[p/4] = sq2(p);
		}
	}
	lli ans = 0;
	for(lli z = 1; z*z <= N; z += 4){
		//if(z % 100000 <= 8) cout << (double)z*z/N*100 << "\n";
		for(auto [x, y] : r2(z)){
			lli a = x*z;
			lli b = y*z;
			lli c = x*y;
			if(a <= N && b <= N && c <= N){
				ans += a+b+c;
				ans %= mod;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}