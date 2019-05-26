#include <iostream>
#include <cmath>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const lli inv2 = 5e8 + 4;

lli sum2(lli n, lli l){
	n = min(n, l);
	n %= mod;
	return n * (n + 1) % mod * inv2 % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, l;
	cin >> n >> l;
	lli ans = (n % mod) * (max(0ll, l-n) % mod) % mod;
	l = min(l, n);
	ans = (ans + (n % mod) * (l % mod) % mod) % mod;
	lli m = sqrt(n);
	for(lli i = 1; i <= n/m && i <= l; ++i){
		ans = (ans - i * (n / i) % mod) % mod;
		while(ans < 0) ans += mod;
	}
	for(lli i = 1; i < m; ++i){
		ans = (ans - (sum2(n / i, l) - sum2(n / (i + 1), l)) * i % mod) % mod;
		while(ans < 0) ans += mod;
	}
	cout << ans << "\n";
	return 0;
}