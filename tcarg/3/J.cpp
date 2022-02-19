#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
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
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, c;
	cin >> n >> m >> c;
	int colours = power(c, n*n);
	int ans = 0;
	for(int i = 1; i <= m; ++i){
		ans += power(colours, __gcd(i, m));
		if(ans >= mod) ans -= mod;
	}
	ans = ans * power(m, mod-2) % mod;
	cout << ans << "\n";
	return 0;
}