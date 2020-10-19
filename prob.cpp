#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int mod = 1e9 + 7;

const int M = 3e5;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

int ncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

int invncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[k] * fact[n-k] % mod * invfact[n] % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	int n, a, q;
	cin >> n >> a >> q;
	while(q--){
		int x, y;
		cin >> x >> y; 
		++y;
		int ans = (lli)(ncr(a + n-x, n-x) - ncr(a + n-y, n-y)) * invncr(a + n-1, n-1) % mod;
		if(ans < 0) ans += mod;
		cout << ans << "\n";
	}
	return 0;
}