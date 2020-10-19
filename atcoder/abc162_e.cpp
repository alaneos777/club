#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

auto phiSieve(int n){
	vector<int> phi(n+1);
	iota(phi.begin(), phi.end(), 0);
	for(int i = 2; i <= n; ++i){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
	return phi;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	auto phi = phiSieve(k);
	int ans = 0;
	for(int i = 1; i <= k; ++i){
		ans += phi[i] * power(k/i, n) % mod;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}