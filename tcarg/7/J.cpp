#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> fact(2001, 1), inv(2001, 1), invfact(2001, 1);
	for(lli i = 2; i <= 2000; ++i){
		fact[i] = i*fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = inv[i] * invfact[i-1] % mod;
	}
	auto ncr = [&](int n, int k) -> lli{
		if(k < 0 || k > n) return 0;
		return fact[n] * invfact[k] % mod * invfact[n-k] % mod;
	};
	int k;
	cin >> k;
	int sum = 0;
	lli ans = 1;
	while(k--){
		int ai;
		cin >> ai;
		sum += ai;
		ans = ans * ncr(sum-1, ai-1) % mod;
	}
	cout << ans << "\n";
	return 0;
}