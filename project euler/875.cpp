#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1001961001;

lli power(lli a, lli b){
	b %= mod-1;
	if(b < 0) b += mod-1;
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<int> sq(const vector<int>& a){
	int n = a.size();
	vector<int> c(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			int idx = (i+j)%n;
			c[idx] += (lli)a[i] * a[j];
			if(c[idx] >= mod) c[idx] -= mod;
		}
	}
	return c;
}

int q_brute(int n){
	vector<int> P(n);
	for(int a = 0; a < n; ++a){
		P[(lli)a*a%n]++;
	}
	P = sq(sq(P));
	int ans = 0;
	for(int i = 0; i < n; ++i){
		ans += (lli)P[i] * P[i] % mod;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

// https://arxiv.org/pdf/1404.4214.pdf

int g(int p, int a){
	if(p == 2){
		// corollary 22
		lli ans = power(7, -1) * (power(2, 3*a) - 1) % mod * power(2, 4*a+3) % mod;
		return ans;
	}else{
		// corollary 5
		lli ans = power(p, 7*a) + (power(p, 7*a) - power(p, 4*a)) * power(power(p, 3) + power(p, 2) + p, -1) % mod;
		ans %= mod;
		if(ans < 0) ans += mod;
		return ans;
	}
}

vector<int> generalSieve(int n){
	vector<int> f(n+1, 1), cnt(n+1), acum(n+1), primes;
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){ //case base: f(p)
			f[i] = g(i, 1);
			primes.push_back(i);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				f[d] = (lli)f[i / acum[i]] * g(p, cnt[i] + 1) % mod;
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				f[d] = (lli)f[i] * g(p, 1) % mod;
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return f;
}

int main(){
	int N = 12345678;
	int ans = 0;
	vector<int> q = generalSieve(N);
	for(int n = 1; n <= N; ++n){
		ans += q[n];
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}