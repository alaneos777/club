#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e16;

lli mem_f[64][2000][2];
lli mem_g[64][2000][2];

lli f(lli n, int a, int b, int pos = 62, bool canUseAll = false, int sum_a = 0, int sum_b = 0){
	if(pos == -1) return sum_a == sum_b;
	lli& ans = mem_f[pos][sum_a - sum_b + 999][canUseAll];
	if(ans != -1) return ans;
	ans = 0;
	int lim = (canUseAll ? 1 : ((n>>pos) & 1));
	for(int d = 0; d <= lim; ++d){
		int add_a = d * (1 << (pos%a));
		int add_b = d * (1 << (pos%b));
		ans += f(n, a, b, pos-1, canUseAll | (d < lim), sum_a + add_a, sum_b + add_b);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

lli M(lli n, int a, int b, int pos = 62, bool canUseAll = false, int sum_a = 0, int sum_b = 0){
	if(pos == -1) return 0;
	lli& ans = mem_g[pos][sum_a - sum_b + 999][canUseAll];
	if(ans != -1) return ans;
	ans = 0;
	int lim = (canUseAll ? 1 : ((n>>pos) & 1));
	for(int d = 0; d <= lim; ++d){
		int add_a = d * (1 << (pos%a));
		int add_b = d * (1 << (pos%b));
		ans += d * __int128_t(1ll << pos) % mod * f(n, a, b, pos-1, canUseAll | (d < lim), sum_a + add_a, sum_b + add_b) % mod + M(n, a, b, pos-1, canUseAll | (d < lim), sum_a + add_a, sum_b + add_b);
		while(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(int k = 3; k <= 6; ++k){
		for(int l = 1; l <= k-2; ++l){
			memset(mem_f, -1, sizeof(mem_f));
			memset(mem_g, -1, sizeof(mem_g));
			ans = (ans + M(1e16, k, l)) % mod;
		}
	}
	cout << ans << "\n";
	return 0;
}