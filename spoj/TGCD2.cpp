#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
 
const lli mod = 1e9 + 7;
const lli inv2 = 5e8 + 4;
const lli inv4 = inv2 * inv2 % mod;
const lli inv6 = 166666668;
const lli limit = 235711131719ll;
const int MX = pow(limit, 2.0 / 3.0);
const lli inf = numeric_limits<lli>::max();
 
int Mu[MX + 1];
 
void muSieve(int n){
	fill(Mu, Mu + n+1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
}
 
inline lli P(lli n){
	n %= mod;
	return n * (n + 1) % mod * inv2 % mod;
}
 
inline lli P2(lli n){
	n %= mod;
	return n * (n + 1) % mod * (2*n + 1) % mod * inv6 % mod;
}
 
inline lli P3(lli n){
	lli t = P(n);
	return t * t % mod;
}
 
lli sq[MX+1], cb[MX+1], sx[MX+1];
 
lli Usmall[MX + 1];
unordered_map<lli, lli> Ubig;
 
lli functionU(lli n){
	if(n <= MX) return Usmall[n];
	if(Ubig.count(n)) return Ubig[n];
	lli m = sqrt(n);
	lli ans = 1;
	for(lli k = 2, l = n/m; k <= l; ++k){
		ans -= functionU(n / k) * sq[k] % mod;
		if(ans < 0) ans += mod;
	}
	for(lli k = 1; k < m; ++k){
		ans -= (P2(n / k) - P2(n / (k + 1))) * Usmall[k] % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return Ubig[n] = ans;
}
 
lli Vsmall[MX + 1];
unordered_map<lli, lli> Vbig;
 
lli functionV(lli n){
	if(n <= MX) return Vsmall[n];
	if(Vbig.count(n)) return Vbig[n];
	lli m = sqrt(n);
	lli ans = 0;
	for(lli k = 1; k <= m; ++k){
		if(Mu[k] == 1)
			ans += sx[k] * P3(n / k / k) % mod;
		else if(Mu[k] == -1)
			ans -= sx[k] * P3(n / k / k) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	return Vbig[n] = ans;
}
 
unordered_map<lli, lli> Hbig;
 
lli functionH(lli n){
	if(n == 0) return 0;
	if(Hbig.count(n)) return Hbig[n];
	lli m = sqrt(n);
	lli ans = 0;
	for(lli k = 1, l = n/m; k <= l; ++k){
		if(Mu[k]) ans += cb[k] * functionU(n / k) % mod;
		if(ans >= mod) ans -= mod;
	}
	for(lli k = 1; k < m; ++k){
		ans += (functionV(n / k) - functionV(n / (k + 1)) + mod) * Usmall[k] % mod;
		if(ans >= mod) ans -= mod;
	}
	return Hbig[n] = ans;
}
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	muSieve(MX);
	for(lli i = 1; i <= MX; ++i){
		sq[i] = i * i % mod;
		cb[i] = sq[i] * i % mod;
		sx[i] = cb[i] * cb[i] % mod;
		if(Mu[i] == 1) Usmall[i] = Usmall[i-1] + sq[i];
		else if(Mu[i] == -1) Usmall[i] = Usmall[i-1] - sq[i];
		else Usmall[i] = Usmall[i-1];
		Vsmall[i] = Vsmall[i-1] + (Mu[i] ? cb[i] : 0);
		if(Usmall[i] >= mod) Usmall[i] -= mod;
		if(Usmall[i] < 0) Usmall[i] += mod;
		if(Vsmall[i] >= mod) Vsmall[i] -= mod;
		if(Vsmall[i] < 0) Vsmall[i] += mod;
	}
	int t;
	cin >> t;
	while(t--){
		lli n, m;
		cin >> n >> m;
		lli M = max(n, m);
		lli ans = 0;
		lli i = 1;
		while(i <= M){
			lli a = i > n ? inf : n / (n / i);
			lli b = i > m ? inf : m / (m / i);
			lli u = min(a, b);
			if(u == inf) break;
			ans += (functionH(u) - functionH(i-1) + mod) * P(n / i) % mod * P(m / i) % mod;
			if(ans >= mod) ans -= mod;
			i = u + 1;
		}
		cout << ans << "\n";
	}
	return 0;
} 