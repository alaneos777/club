#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

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

const int M = 1e7;
const auto primes = sieve(M);

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

lli naive(lli p){
	for(lli n = 0; n < p*p; ++n){
		lli eval = (n*n - 3*n + 1) % (p*p);
		if(eval < 0) eval += p*p;
		if(eval == 0){
			return eval;
		}
	}
	return 0;
}

int main(){
	int64_t ans = 0;
	for(int p : primes){
		if(p == 2 || p == 13){
			ans += naive(p);
			continue;
		}
		if(power(13, (p-1)/2, p) == p-1) continue;
		lli sqrt13 = sqrtMod(13, p);
		lli q = (lli)p*p;
		sqrt13 = power(sqrt13, p, q) * power(13, (lli)(p-1)*(p-1)/2, q) % q;
		lli inv2 = power(2, q - p - 1, q);
		lli x1 = (3 + sqrt13) * inv2 % q;
		lli x2 = (3 + q-sqrt13) * inv2 % q;
		if(x1 > x2) swap(x1, x2);
		ans += x1;
	}
	cout << ans << "\n";
	return 0;
}