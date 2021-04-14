#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q, l, r;
	lli k, a, b;
	cin >> n >> k >> a >> b;
	k %= mod, a %= mod, b %= mod;
	vector<int> inv(n+1, 1), dp(n+1), ans(n+1);
	for(lli i = 2; i <= n; ++i){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
	dp[1] = k, dp[2] = (a + b*k) % mod * k % mod;
	for(int i = 3; i <= n; ++i){
		dp[i] = ((a + 2*b*k) % mod * (2*i-3) % mod * dp[i-1] % mod - a*a % mod * (i-3) % mod * dp[i-2] % mod) * inv[i] % mod;
		if(dp[i] < 0) dp[i] += mod;
	}
	for(int i = 1; i <= n; ++i){
		ans[i] = ans[i-1] + (lli)dp[i] * dp[i] % mod;
		if(ans[i] >= mod) ans[i] -= mod;
	}
	cin >> q;
	while(q--){
		cin >> l >> r;
		int res = ans[r] - ans[l-1];
		if(res < 0) res += mod;
		cout << res << "\n";
	}
	return 0;
}