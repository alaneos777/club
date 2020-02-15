#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

const int M = 1e6;

vector<int> muSieve(int n){
	vector<int> Mu(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}

const vector<int> Mu = muSieve(M);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> f(M+1);
	for(int i = 1; i <= M; ++i){
		for(int j = i; j <= M; j += i){
			f[j] = (f[j] + i * Mu[i]) % mod;
			if(f[j] < 0) f[j] += mod;
		}
	}

	vector<lli> inv(M+1);
	inv[1] = 1;
	for(int i = 2; i <= M; ++i){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}

	int n;
	cin >> n;
	vector<lli> freq(M+1);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		freq[ai]++;
	}

	vector<lli> g(M+1);
	for(int i = 1; i <= M; ++i){
		for(int j = i; j <= M; j += i){
			g[i] = (g[i] + j * freq[j] % mod) % mod;
		}
	}

	lli ans = 0;
	for(int d = 1; d <= M; ++d){
		ans = (ans + f[d] * g[d] % mod * g[d] % mod * inv[d] % mod - d * freq[d] % mod) % mod;
	}
	ans = ans * inv[2] % mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}
