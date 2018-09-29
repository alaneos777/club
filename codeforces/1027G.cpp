#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef pair<lli, int> pii;

vector<int> primes;
void sieve(int n){
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i])
			primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
}

vector<pii> factorize(lli n){
	vector<pii> f;
	for(lli p : primes){
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			while(n % p == 0) n /= p, ++pot;
			f.emplace_back(p, pot);
		}
	}
	if(n > 1) f.emplace_back(n, 1);
	return f;
}

lli multMod(lli a, lli b, lli n){
	lli ans = 0;
	a %= n, b %= n;
	if(abs(b) > abs(a)) swap(a, b);
	if(b < 0){
		a *= -1, b *= -1;
	}
	while(b){
		if(b & 1) ans = (ans + a) % n;
		b >>= 1;
		a = (a + a) % n;
	}
	return ans;
}

lli pow(lli b, lli e){
	lli ans = 1;
	while(e){
		if(e & 1) ans *= b;
		e >>= 1;
		b *= b;
	}
	return ans;
}

lli powMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = multMod(ans, b, m);
		e >>= 1;
		b = multMod(b, b, m);
	}
	return ans;
}

lli multiplicativeOrder(lli x, lli m, lli order){
	auto f = factorize(order);
	for(auto & factor : f){
		lli p = factor.first;
		int a = factor.second;
		order /= pow(p, a);
		lli tmp = powMod(x, order, m);
		while(tmp != 1){
			tmp = powMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli m, x;
	cin >> m >> x;
	sieve(sqrt(m) + 10);
	auto f = factorize(m);
	lli ans = 0;
	function<void(vector<pii>, int, lli)> dfs = [&](vector<pii> acum, int pos, lli d){
		if(pos == f.size()){
			lli phi_d = d;
			for(auto & factor : acum){
				if(factor.second) phi_d -= phi_d / factor.first;
			}
			ans += phi_d / multiplicativeOrder(x, d, phi_d);
			return;
		}
		lli prod = d;
		for(int i = 0; i <= f[pos].second; ++i){
			dfs(acum, pos + 1, prod);
			acum[pos].second++;
			prod *= f[pos].first;
		}
	};
	vector<pii> acum;
	for(auto factor : f){
		acum.emplace_back(factor.first, 0);
	}
	dfs(acum, 0, 1);
	cout << ans << "\n";
	return 0;
}