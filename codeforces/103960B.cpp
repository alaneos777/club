#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli count_ones(lli n, int i){
	if(n <= 0) return 0ll;
	lli ans = ((n + 1) >> (i + 1)) << i;
	ans += max(((n + 1) & ((1ll << (i + 1)) - 1)) - (1ll << i), 0ll);
	return ans;
}

lli count_ones(lli l, lli r, int i){
	return count_ones(r, i) - count_ones(l-1, i);
}

lli count_zeros(lli l, lli r, int i){
	return r-l+1 - count_ones(l, r, i);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli l1, r1, l2, r2, l3, r3;
	cin >> l1 >> r1 >> l2 >> r2 >> l3 >> r3;
	lli ans = 1;
	for(int i = 0; i < 30; ++i){
		lli cnt = 0;
		cnt += count_zeros(l1, r1, i) * count_zeros(l2, r2, i) % mod * count_zeros(l3, r3, i) % mod;
		cnt += count_zeros(l1, r1, i) * count_ones(l2, r2, i) % mod * count_ones(l3, r3, i) % mod;
		cnt += count_ones(l1, r1, i) * count_zeros(l2, r2, i) % mod * count_ones(l3, r3, i) % mod;
		cnt += count_ones(l1, r1, i) * count_ones(l2, r2, i) % mod * count_zeros(l3, r3, i) % mod;
		cnt %= mod;
		ans = ans * cnt % mod;
	}
	ans = ans * powerMod(r1-l1+1, mod-2) % mod * powerMod(r2-l2+1, mod-2) % mod * powerMod(r3-l3+1, mod-2) % mod;
	ans = (1-ans) % mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}