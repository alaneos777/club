#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

const int M = 2e5;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

const int MX = 1e6;

lli ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	return (lli)fact[n] * invfact[r] % mod * invfact[n-r] % mod;
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

auto divsSieve(int n){
	vector<vector<int>> divs(n);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

const auto phi = phiSieve(MX);
const auto divs = divsSieve(MX);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	int n, k, q;
	cin >> n >> k >> q;
	vector<int> freq(MX+1);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		freq[ai]++;
	}
	vector<int> cnt(MX+1);
	for(int d = 1; d <= MX; ++d){
		for(int e = d; e <= MX; e += d){
			cnt[d] += freq[e];
		}
	}
	lli ans = 0;
	for(int d = 1; d <= MX; ++d){
		ans += phi[d] * ncr(cnt[d], k) % mod;
		if(ans >= mod) ans -= mod;
	}
	for(int i = 0; i < q; ++i){
		int ci;
		cin >> ci;
		for(int d : divs[ci]){
			ans -= phi[d] * ncr(cnt[d], k) % mod;
			if(ans < 0) ans += mod;
			cnt[d]++;
			ans += phi[d] * ncr(cnt[d], k) % mod;
			if(ans >= mod) ans -= mod;
		}
		cout << ans << "\n";
	}
	return 0;
}