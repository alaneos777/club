#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

inline lli modula(lli a){
	while(a >= mod) a -= mod;
	while(a < 0) a += mod;
	return a;
}


int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	lli k, a, b;
	cin >> n >> k >> a >> b;
	vector<lli> inv(n+1);
	inv[1] = 1;
	for(lli i = 2; i <= n; ++i)
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	vector<lli> dp(3);
	dp[1] = k%mod;
	dp[2] = modula(a*k%mod + b*k%mod*k%mod);
	lli a2 = a * a % mod;
	lli prod = (a + 2*b*k%mod) % mod;
	for(lli i = 3; i <= n; ++i){
		dp[((i-1)&1)+1] = modula((2*i - 3) * prod % mod * dp[((i-2)&1)+1] % mod - a2*(i-3)%mod*dp[((i-3)&1)+1]%mod) * inv[i] % mod;
	}
	cout << dp[((n-1)&1)+1] << "\n";
	return 0;
}