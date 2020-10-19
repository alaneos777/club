#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const int M = 5e5;
const lli mod = 998244353;
const auto phi = phiSieve(M);

lli power(lli a, lli b){
	b %= mod-1;
	if(b < 0) b += mod-1;
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
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> freq(M+1), cnt(M+1);
		for(int i = 0; i < n; ++i){
			int ai;
			cin >> ai;
			freq[ai]++;
		}
		for(int i = 1; i <= M; ++i){
			for(int j = i; j <= M; j += i){
				cnt[i] += freq[j];
			}
		}
		int ans = 0;
		for(int i = 1; i <= M; ++i){
			ans += (lli)phi[i] * cnt[i] % mod * cnt[i] % mod;
			if(ans >= mod) ans -= mod;
		}
		ans = (lli)ans * n % mod * (n+1) % mod * (2*n+1) % mod * power(6, -1) % mod * power(n, -3) % mod;
		cout << ans << "\n";
	}
	return 0;
}