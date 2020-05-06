#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

auto muSieve(int n){
	vector<int> mu(n+1, -1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(mu[i]){
			for(int j = 2*i; j <= n; j += i){
				mu[j] -= mu[i];
			}
		}
	}
	return mu;
}

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

vector<int> fact, inv, invfact;
void getFact(int n){
	fact.resize(n+1, 1);
	inv.resize(n+1, 1);
	invfact.resize(n+1, 1);
	for(lli i = 2; i <= n; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
}

const int M = 1e5;
const auto mu = muSieve(M);
const auto divs = divsSieve(M);

lli ncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

int main(){
	getFact(M);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int q;
	cin >> q;
	while(q--){
		int n, f;
		cin >> n >> f;
		lli ans = 0;
		for(int d : divs[n]){
			if(mu[d] == 0) continue;
			ans += mu[d] * ncr(n/d - 1, f - 1);
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
		}
		cout << ans << "\n";
	}
	return 0;
}