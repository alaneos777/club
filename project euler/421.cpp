#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

vector<int> sieve(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

const int M = 1e8;
const lli limit = 1e11;
const auto lp = sieve(M);

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

bool isGenerator(int g, int p){
	int order = p - 1;
	while(order > 1){
		int prime = lp[order];
		while(order % prime == 0) order /= prime;
		if(power(g, (p - 1) / prime, p) == 1) return false;
	}
	return true;
}

int generator(int p){
	for(int g = 1; g < p; ++g){
		if(isGenerator(g, p)) return g;
	}
	assert(0);
}

vector<int> getSols(int p){
	if(p == 2) return {1};
	int d = __gcd(15, (p - 1) / 2);
	int lhs = 15 / d, rhs = (p - 1) / 2 / d;
	int cnt = __gcd(p - 1, d);
	int mod = (p - 1) / cnt;
	if(__gcd(lhs, mod) != 1) return {};
	int g = generator(p);
	int k = (lli)rhs * inverse(lhs, mod) % mod;
	vector<int> ans(cnt);
	ans[0] = power(g, k, p);
	lli mult = power(g, mod, p);
	for(int i = 1; i < cnt; ++i){
		ans[i] = ans[i-1] * mult % p;
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(int p = 2; p <= M; ++p){
		if(lp[p] != p) continue;
		vector<int> sols = getSols(p);
		for(int sol : sols){
			ans += (lli)p * ((limit - sol) / p + 1);
		}
	}
	cout << ans << "\n";
	return 0;
}