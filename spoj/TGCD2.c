#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef long long int lli;

const lli mod = 1e9 + 7;
const lli inv2 = 5e8 + 4;
const lli inv4 = 2.5e8 + 2;
const lli inv6 = 166666668;
#define MX 70300000
#define mx 100000

lli threshold, L;

int8_t Mu[MX + 1];
uint8_t isPrime[MX + 1];
int primes[(MX + 1) / 10];
int sz = 0;

void muSieve(int n){
	Mu[0] = 0, Mu[1] = 1;
	memset(isPrime, 1, n);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes[sz++] = i;
			Mu[i] = -1;
		}
		for(int j = 0; j < sz; ++j){
			int p = primes[j];
			int d = i * p;
			if(d > n) break;
			isPrime[d] = 0;
			if(i % p == 0){
				break;
			}else{
				Mu[d] = -Mu[i];
			}
		}
	}
}

lli P(lli n){
	n %= mod;
	return n * (n + 1) % mod * inv2 % mod;
}

lli P2(lli n){
	n %= mod;
	return n * (n + 1) % mod * (2*n + 1) % mod * inv6 % mod;
}

lli P3(lli n){
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
		ans -= (lli)functionU(n / k) * sq[k] % mod;
		if(ans < 0) ans += mod;
	}
	for(int k = 1; k < m; ++k){
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
		if(Mu[k]) ans += (lli)cb[k] * functionU(n / k) % mod;
		if(ans >= mod) ans -= mod;
	}
	for(lli k = 1; k < m; ++k){
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

lli qa[10010];
lli qb[10010];

int main(){
	int t;
	scanf("%d", &t);
	for(int i = 0; i < t; ++i){
		scanf("%lld %lld", &qa[i], &qb[i]);
		L = L > qa[i] ? L : qa[i];
		L = L > qb[i] ? L : qb[i];
	}
	threshold = pow(L * 2.5, 2.0 / 3.0);
	muSieve(threshold);
	for(int i = 1; i <= threshold; ++i){
		Hsmall[i] = -1;
	}
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
	for(int c = 0; c < t; ++c){
		n = qa[c], m = qb[c];
		M = n < m ? n : m;
		ans = 0;
		i = 1;
		while(i <= M){
			ni = n / i, mi = m / i;
			u = n / ni < m / mi ? n / ni : m / mi;
			ans += (functionH(u) - functionH(i-1) + mod) * P(ni) % mod * P(mi) % mod;
			if(ans >= mod) ans -= mod;
			i = u + 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}