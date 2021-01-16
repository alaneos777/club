#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	int n, m, c;
	cin >> n >> m >> c;
	lli colors = power(c, n*n);
	lli ans = 0;
	for(int i = 0; i < m; ++i){
		ans += power(colors, __gcd(i, m));
		if(ans >= mod) ans -= mod;
	}
	ans = ans * power(m, mod-2) % mod;
	cout << ans << "\n";
	return 0;
}