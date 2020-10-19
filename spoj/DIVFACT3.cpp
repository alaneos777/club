#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

vector<int> primes, pi;
void sieve(int n){
	vector<bool> is(n+1, true);
	pi.resize(n+1);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	for(int i = 1; i <= n; ++i){
		pi[i] = pi[i-1] + is[i];
	}
}

lli pot(lli n, lli p, lli m){
	lli ans = 0;
	while(n /= p) ans += n;
	return ans % m;
}

lli power(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(1e8);
	int t;
	cin >> t;
	while(t--){
		lli n, m;
		cin >> n >> m;
		if(n == 0){
			cout << 1ll%m << "\n";
			continue;
		}
		lli ans = 1;
		lli v = sqrt(n);
		lli lim = n/v;
		for(lli p : primes){
			if(p > lim) break;
			ans = ans * (pot(n, p, m) + 1) % m;
		}
		for(lli i = 1; i < v; ++i){
			ans = ans * power(i + 1, pi[n / i] - pi[n / (i + 1)], m) % m;
		}
		cout << ans << "\n";
	}
	return 0;
}