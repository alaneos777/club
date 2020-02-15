#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

int naive(int n){
	vector<int> pi(n);
	for(int i = 0; i < n; ++i){
		if(i % 2 == 0){
			pi[i] = i/2;
		}else{
			pi[i] = i/2 + n/2;
		}
	}
	vector<bool> vis(n);
	int ans = 1;
	for(int u = 0; u < n; ++u){
		if(vis[u]) continue;
		int start = u;
		vis[u] = true;
		int len = 0;
		while(true){
			u = pi[u];
			vis[u] = true;
			len++;
			if(u == start) break;
		}
		ans = ans / __gcd(ans, len) * len;
	}
	return ans;
}

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

bool isPrime(int64_t n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	int64_t d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = power(a, d, n);
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t aleatorio(int64_t a, int64_t b){
	std::uniform_int_distribution<int64_t> dist(a, b);
	return dist(rng);
}
int64_t getFactor(int64_t n){
	int64_t a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = __gcd((int64_t)abs(x - y), n);
	}
	return d;
}

map<int64_t, int> fact;
void factorize(int64_t n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrime(n)){
		int64_t f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorize(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

int64_t phi(int64_t n){
	factorize(n);
	for(const auto & par : fact){
		n -= n / par.first;
	}
	return n;
}

int64_t order(int64_t x, int64_t m){
	int64_t order = phi(m);
	factorize(order);
	for(const auto & par : fact){
		int64_t p; int a;
		tie(p, a) = par;
		while(a--) order /= p;
		int64_t tmp = power(x, order, m);
		while(tmp != 1){
			tmp = power(tmp, p, m);
			order *= p;
		}
	}
	return order;
}

int main(){
	uint64_t sum = 0;
	int n = 60;
	int64_t N = (1ll<<n) - 1;
	factorize(N);
	auto f = fact;
	function<void(map<int64_t, int>::iterator, int64_t)> dfs = [&](map<int64_t, int>::iterator it, int64_t d){
		if(it == f.end()){
			if(order(2, d) == n){
				sum += d+1;
			}
		}else{
			int64_t p; int a;
			tie(p, a) = *it;
			int64_t p_pow = 1;
			auto it2 = it; ++it2;
			for(int i = 0; i <= a; ++i){
				dfs(it2, d * p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(f.begin(), 1);
	cout << sum;
	return 0;
}