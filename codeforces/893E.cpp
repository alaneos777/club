#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 1.1e6;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

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

const auto lp = lpSieve(M);

lli ncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}

auto factorize(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		f.emplace_back(p, a);
	}
	return f;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	int t;
	cin >> t;
	while(t--){
		int x, y;
		cin >> x >> y;
		lli ans = power(2, y-1);
		for(auto[p, a] : factorize(x)){
			ans = ans * ncr(a + y-1, y-1) % mod;
		}
		cout << ans << "\n";
	}
	return 0;
}