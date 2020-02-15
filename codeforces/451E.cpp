#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

map<lli, lli> mult(const map<lli, lli> & a, const map<lli, lli> & b){
	map<lli, lli> c;
	for(const auto & p1 : a){
		for(const auto & p2 : b){
			(c[p1.first + p2.first] += p1.second * p2.second) %= mod;
		}
	}
	return c;
}

lli inv(lli a){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += mod;
	return s0;
}

lli ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	n %= mod;
	if(r < 0 || r > n) return 0;
	r = min(r, n - r);
	lli ans = 1;
	for(lli den = 1, num = n; den <= r; ++den, --num){
		ans = ans * num % mod * inv(den) % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n; lli s;
	cin >> n >> s;
	map<lli, lli> p = {{0, 1}};
	for(int i = 0; i < n; ++i){
		lli fi;
		cin >> fi;
		p = mult(p, {{0, 1}, {fi + 1, mod - 1}});
	}
	lli ans = 0;
	for(const auto & par : p){
		(ans += ncr(s - par.first + n - 1, n - 1) * par.second) %= mod;
	}
	cout << ans << "\n";
	return 0;
}