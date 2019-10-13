#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
 
const lli mod = 1e9 + 7;
const lli MX = 1e6 + 10;
lli f[MX+1], g[MX+1], G[MX+1];
 
void sieve(int n){
	f[0] = 0, f[1] = 1;
	for(int i = 2; i <= n; ++i) f[i] = ((i & 1) ? i : 2);
	for(int i = 3; i * i <= n; i += 2)
		if(f[i] == i)
			for(int j = i * i; j <= n; j += 2*i)
				if(f[j] == j) f[j] = i;
	g[1] = G[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(f[i] == i){
			f[i] = i - 1;
		}else{
			int p = f[i];
			int m = i / p;
			if(m % p == 0){
				m /= p;
				if(m % p == 0){
					f[i] = 0;
				}else{
					f[i] = f[m] * (mod - p) % mod;
				}
			}else{
				f[i] = f[m] * (p - 1) % mod;
			}
		}
		g[i] = (lli)i * i % mod * f[i] % mod;
		G[i] = G[i-1] + g[i];
		if(G[i] >= mod) G[i] += mod;
	}
}
 
lli P(lli n){
	return n * (n + 1) / 2 % mod;
}
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(MX);
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		int M = max(n, m);
		lli ans = 0;
		int i = 1;
		while(i <= M){
			int a = i > n ? mod : n / (n / i);
			int b = i > m ? mod : m / (m / i);
			int u = min(a, b);
			if(u == mod) break;
			ans += (G[u] - G[i-1] + mod) * P(n / i) % mod * P(m / i) % mod;
			if(ans >= mod) ans -= mod;
			i = u + 1;
		}
		cout << ans << "\n";
	}
	return 0;
} 