#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli p){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return ans;
}

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const int L = 3e6;
const auto lp = lpSieve(L);

bool isPrime(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

auto factorize(int n){
	vector<int> pr;
	while(n > 1){
		int p = lp[n];
		while(n % p == 0) n /= p;
		pr.push_back(p);
	}
	return pr;
}

lli generator(lli m){
	lli order = m-1;
	auto f = factorize(order);
	for(lli x = 1; x < m; x++){
		if(__gcd(x, m) != 1) continue;
		bool test = true;
		for(int p : f){
			if(powerMod(x, order / p, m) == 1){
				test = false;
				break;
			}
		}
		if(test) return x;
	}
	return -1;
}

const int N = 360, M = 20;
int w_pow[N];

lli dp[2][M+1][L+1];

int main(){
	for(int r = 4000; 1 + N*r <= L; ++r){
		int p = 1 + N*r;
		if(lp[p] != p) continue;

		int g = generator(p);
		int w = powerMod(g, (p-1)/N, p);
		cout << "p=" << p << ", g=" << g << ": ";

		w_pow[0] = 1;
		for(int i = 1; i < N; ++i){
			w_pow[i] = (lli)w_pow[i-1] * w % p;
		}

		memset(dp, 0, sizeof(dp));

		dp[0][0][0] = 1;
		for(int pos = 1; pos <= N; ++pos){
			for(int cnt = 0; cnt <= M; ++cnt){
				for(int sum = 0; sum < p; ++sum){
					int new_sum = sum + w_pow[pos-1];
					if(new_sum >= p) new_sum -= p;
					dp[pos&1][cnt][sum] = dp[(pos-1)&1][cnt][sum] + (cnt > 0 ? dp[(pos-1)&1][cnt-1][new_sum] : 0);
				}
			}
		}

		cout << dp[N&1][M][0] << "\n";
	}
	return 0;
}