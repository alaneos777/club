#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
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

const int M = 1.5e8 + 100;
const auto primes = sieve(M);

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli sqrtMod(lli a, lli p){
	a %= p;
	if(a == 0) return 0;
	if(power(a, (p - 1) / 2, p) != 1) return -1;
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

const vector<int> values = {1, 3, 7, 9, 13, 27};

__int128 powerMod(__int128 a, __int128 b, __int128 m){
	__int128 ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrime(__int128 n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	__int128 d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		__int128 m = powerMod(a, d, n);
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

int main(){
	vector<vector<bool>> is(values.size(), vector<bool>(M+1, true));
	for(int p : primes){
		for(int v = 0; v < values.size(); ++v){
			int val = values[v];
			int rhs = (-val) % p;
			if(rhs < 0) rhs += p;
			int r0 = sqrtMod(rhs, p);
			if(r0 == -1) continue;
			int r1 = (p - r0) % p;
			bool flg = true;
			for(int i = r0; i <= M; i += p){
				if(flg && (lli)i*i+val == p){
					flg = false;
					continue;
				}
				is[v][i] = false;
			}
			if(r1 == r0) continue;
			for(int i = r1; i <= M; i += p){
				if(flg && (lli)i*i+val == p){
					flg = false;
					continue;
				}
				is[v][i] = false;
			}
		}
	}
	lli sum = 0;
	for(int n = 1; n <= M; ++n){
		bool test = true;
		for(int v = 0; v < values.size(); ++v){
			test &= is[v][n];
		}
		if(test){
			for(int v = 0; v < values.size()-1; ++v){
				for(int i = values[v]+1; i <= values[v+1]-1; ++i){
					test &= !isPrime((lli)n*n + i);
				}
			}
			if(test){
				cout << " " << n << "\n";
				sum += n;
			}
		}
	}
	cout << sum << "\n";
	return 0;
}