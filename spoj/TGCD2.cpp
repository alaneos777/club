#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const lli inv2 = 5e8 + 4;
const lli inv4 = 2.5e8 + 2;
const lli inv6 = 166666668;
const int MX = 0.8e8;
const int mx = 1e5;
lli threshold, L;

int8_t Mu[MX + 1];
bitset<MX+1> isPrime;
vector<int> primes;

void muSieve(int n){
	Mu[0] = 0, Mu[1] = 1;
	isPrime.set();
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
			Mu[i] = -1;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){
				break;
			}else{
				Mu[d] = -Mu[i];
			}
		}
	}
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

int sq[MX+1], cb[MX+1], sx[MX+1];

int Usmall[MX + 1];
lli Ubig_key[mx][4];
int Ubig_value[mx][4];
int8_t Ubig_sz[mx];

int functionU(lli n){
	if(n <= threshold) return Usmall[n];
	int key = L / n;
	for(int i = 0; i < Ubig_sz[key]; ++i){
		if(Ubig_key[key][i] == n) return Ubig_value[key][i];
	}
	lli m = sqrt(n);
	int ans = 1;
	for(int k = 2, l = n/m; k <= l; ++k){
		assert(k <= threshold);
		ans -= (lli)functionU(n / k) * sq[k] % mod;
		if(ans < 0) ans += mod;
	}
	for(int k = 1; k < m; ++k){
		assert(k <= threshold);
		ans -= (P2(n / k) - P2(n / (k + 1))) * Usmall[k] % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	Ubig_key[key][Ubig_sz[key]] = n;
	Ubig_value[key][Ubig_sz[key]] = ans;
	Ubig_sz[key]++;
	return ans;
}

int Vsmall[MX + 1];
lli Vbig_key[mx][4];
int Vbig_value[mx][4];
int8_t Vbig_sz[mx];

int functionV(lli n){
	if(n <= threshold) return Vsmall[n];
	int key = L / n;
	for(int i = 0; i < Vbig_sz[key]; ++i){
		if(Vbig_key[key][i] == n) return Vbig_value[key][i];
	}
	lli m = sqrt(n);
	int ans = 0;
	for(lli k = 1; k <= m; ++k){
		assert(k <= threshold);
		if(Mu[k] == 1)
			ans += sx[k] * P3(n / (k * k)) % mod;
		else if(Mu[k] == -1)
			ans -= sx[k] * P3(n / (k * k)) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
	}
	Vbig_key[key][Vbig_sz[key]] = n;
	Vbig_value[key][Vbig_sz[key]] = ans;
	Vbig_sz[key]++;
	return ans;
}

int Hsmall[MX + 1];
lli Hbig_key[mx][4];
int Hbig_value[mx][4];
int8_t Hbig_sz[mx];

int functionH(lli n){
	if(n == 0) return 0;
	int key = L / n;
	if(n <= threshold){
		if(Hsmall[n] != -1) return Hsmall[n];
	}else{
		for(int i = 0; i < Hbig_sz[key]; ++i){
			if(Hbig_key[key][i] == n) return Hbig_value[key][i];
		}
	}
	lli m = sqrt(n);
	lli ans = 0;
	for(lli k = 1, l = n/m; k <= l; ++k){
		assert(k <= threshold);
		if(Mu[k]) ans += (lli)cb[k] * functionU(n / k) % mod;
		if(ans >= mod) ans -= mod;
	}
	for(lli k = 1; k < m; ++k){
		assert(k <= threshold);
		ans += (lli)(functionV(n / k) - functionV(n / (k + 1)) + mod) * Usmall[k] % mod;
		if(ans >= mod) ans -= mod;
	}
	if(n <= threshold){
		Hsmall[n] = ans;
	}else{
		Hbig_key[key][Hbig_sz[key]] = n;
		Hbig_value[key][Hbig_sz[key]] = ans;
		Hbig_sz[key]++;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	vector<pair<lli, lli>> queries(t);
	for(auto & qi : queries){
		cin >> qi.first >> qi.second;
		L = max({L, qi.first, qi.second});
	}
	threshold = pow(L * 2.5, 2.0 / 3.0);
	muSieve(threshold);
	fill(Hsmall, Hsmall + threshold + 1, -1);
	for(lli i = 1; i <= threshold; ++i){
		sq[i] = i * i % mod;
		cb[i] = sq[i] * i % mod;
		sx[i] = (lli)cb[i] * cb[i] % mod;
		if(Mu[i] == 1) Usmall[i] = Usmall[i-1] + sq[i];
		else if(Mu[i] == -1) Usmall[i] = Usmall[i-1] - sq[i];
		else Usmall[i] = Usmall[i-1];
		Vsmall[i] = Vsmall[i-1] + (Mu[i] ? cb[i] : 0);
		if(Usmall[i] >= mod) Usmall[i] -= mod;
		if(Usmall[i] < 0) Usmall[i] += mod;
		if(Vsmall[i] >= mod) Vsmall[i] -= mod;
	}
	lli n, m, M, ans, i, ni, mi, u;
	for(auto & qi : queries){
		tie(n, m) = qi;
		M = min(n, m);
		ans = 0;
		i = 1;
		while(i <= M){
			ni = n / i, mi = m / i;
			u = min(n / ni, m / mi);
			ans += (functionH(u) - functionH(i-1) + mod) * P(ni) % mod * P(mi) % mod;
			if(ans >= mod) ans -= mod;
			i = u + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}