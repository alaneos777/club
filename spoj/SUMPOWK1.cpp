#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 == -1) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli mod = 1e8 + 7;
	int t, k;
	cin >> t;
	lli inv_2 = inv(2, mod);
	lli inv_4 = inv(4, mod);
	lli inv_6 = inv(6, mod);
	lli inv_12 = inv(12, mod);
	lli inv_30 = inv(30, mod);
	while(t--){
		lli n, ans = 0;
		cin >> n >> k;
		n %= mod;
		if(k == 0) ans = n;
		else if(k == 1) ans = n * (n + 1) % mod * inv_2 % mod;
		else if(k == 2) ans = n * (n + 1) % mod * (2*n + 1) % mod * inv_6 % mod;
		else if(k == 3) ans = n * n % mod * (n + 1) % mod * (n + 1) % mod * inv_4 % mod;
		else if(k == 4) ans = n * (n + 1) % mod * (2*n + 1) % mod * (3*n*n%mod + 3*n - 1) % mod * inv_30 % mod;
		else if(k == 5) ans = n * n % mod * (n + 1) % mod * (n + 1) % mod * (2*n*n%mod + 2*n - 1) % mod * inv_12 % mod;
		if(ans < 0) ans += mod;
		cout << ans << "\n";
	}
	return 0;
}