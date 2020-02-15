#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

vector<int> sieve(int n){
	vector<bool> is(n + 1, true);
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

vector<int> sieve2(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

const int M = 1e8;
const auto primes = sieve(M);
const auto lp = sieve2(M);

lli sqrtMod(lli a, lli p){
	if(p % 4 == 3) return power(a, (p + 1) / 4, p);
	lli s = p - 1;
	int r = 0;
	while((s & 1) == 0) ++r, s >>= 1;
	lli n = 2;
	while(power(n, (p - 1) / 2, p) != p - 1) ++n;
	lli x = power(a, (s + 1) / 2, p);
	lli b = power(a, s, p);
	lli g = power(n, s, p);
	while(true){
		lli t = b;
		int m = 0;
		for(; m < r; ++m){
			if(t == 1) break;
			t = t * t % p;
		}
		if(m == 0) return x;
		lli gs = power(g, 1 << (r - m - 1), p);
		g = gs * gs % p;
		x = x * gs % p;
		b = b * g % p;
		r = m;
	}
}

bool isGenerator(int a, int p){
	if(a == 0) return false;
	int order = p-1;
	while(order > 1){
		int prime = lp[order];
		while(order % prime == 0) order /= prime;
		if(power(a, (p-1) / prime, p) == 1) return false;
	}
	return true;
}

int main(){
	lli ans = 5;
	for(int p : primes){
		if(!(p%10 == 1 || p%10 == 9)) continue;
		lli sqrt5 = sqrtMod(5, p);
		lli inv2 = (p + 1) >> 1;
		int x1 = (1 + sqrt5) * inv2 % p;
		int x2 = 1 - x1; if(x2 < 0) x2 += p;
		if(isGenerator(x1, p) || isGenerator(x2, p)){
			ans += p;
		}
	}
	cout << ans << "\n";
	return 0;
}