#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int MX = 1.5e7;

vector<int8_t> Mu;
bitset<MX+1> isPrime;
vector<int> primes;

const int mod = 1e9 + 7;

void muSieve(int n){
	Mu.resize(n+1);
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

vector<int> Usmall;
unordered_map<int, int> Ubig;

int threshold = 0;

int U(int n){
	if(n <= threshold) return Usmall[n];
	if(Ubig.find(n) != Ubig.end()) return Ubig[n];
	int m = sqrt(n);
	int ans = 1;
	for(int k = 2, l = n/m; k <= l; ++k){
		ans -= U(n / k);
		if(ans < 0) ans += mod-1;
	}
	for(int k = 1; k < m; ++k){
		ans -= (lli)(n / k - n / (k + 1)) * U(k) % (mod-1);
		if(ans >= mod-1) ans -= mod-1;
		if(ans < 0) ans += mod-1;
	}
	return Ubig[n] = ans;
}

int S(int n, int m){
	int ans = 0;
	int M = min(m, n);
	int i = 1;
	while(i <= M){
		int ni = n / i, mi = m / i;
		int u = min(n / ni, m / mi);
		ans += (lli)(U(u) - U(i-1)) * ni % (mod-1) * mi % (mod-1);
		if(ans >= mod-1) ans -= mod-1;
		if(ans < 0) ans += mod-1;
		i = u + 1;
	}
	return ans;
}

lli powerMod(lli a, lli b){
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
	int n, m;
	cin >> n >> m;
	threshold = pow(max(n, m), 2.0 / 3.0);
	muSieve(threshold);
	Usmall.resize(threshold+1);
	for(int i = 1; i <= threshold; ++i){
		Usmall[i] = Usmall[i-1] + Mu[i];
		if(Usmall[i] >= mod-1) Usmall[i] -= mod-1;
	}
	int ans = 1;
	for(int i = 1; i <= n && i <= m; ++i){
		ans = (lli)ans * powerMod(i, S(n / i, m / i)) % mod;
	}
	cout << ans << "\n";
	return 0;
}