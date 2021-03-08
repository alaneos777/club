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

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

int pot(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

void gen_partitions(int n, function<void(const vector<int>&)> f){
	vector<int> a(n);
	int k = 1, y = n-1;
	while(k != 0){
		int x = a[k-1] + 1;
		k--;
		while(2*x <= y){
			a[k] = x;
			y -= x;
			k++;
		}
		int l = k+1;
		while(x <= y){
			a[k] = x;
			a[l] = y;
			f(vector<int>(a.begin(), a.begin() + k+2));
			x++;
			y--;
		}
		a[k] = x+y;
		y = x+y-1;
		f(vector<int>(a.begin(), a.begin() + k+1));
	}
}

using poly = vector<int>;

poly operator*(const poly & a, const poly & b){
	poly c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += (lli)a[i]*b[j] % mod;
			if(c[i+j] >= mod) c[i+j] -= mod;
		}
	}
	return c;
}

poly inverse(const poly & a, int sz){
	lli inv_a0 = power(a[0], mod-2);
	poly b(sz);
	b[0] = inv_a0;
	for(int i = 1; i < sz; ++i){
		for(int j = 1; j <= i && j < a.size(); ++j){
			b[i] -= (lli)a[j]*b[i-j] % mod;
			if(b[i] < 0) b[i] += mod;
		}
		b[i] = b[i] * inv_a0 % mod;
	}
	return b;
}

int main(){
	int N = 10000, k = 30;

	vector<int> fact(k+1, 1);
	for(lli i = 2; i <= k; ++i){
		fact[i] = i*fact[i-1] % mod;
	}

	vector<vector<int>> ncr(k+1, vector<int>(k+1));
	for(int i = 0; i <= k; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
		}
	}

	vector<int> primes = sieve(N);
	vector<int> exponents;
	for(int p : primes){
		exponents.push_back(pot(N, p));
	}
	int sz = primes.size();

	lli ans = 0;
	gen_partitions(k, [&](const vector<int> & part){
		vector<int> c(k+1);
		for(int p : part){
			c[p]++;
		}
		lli coef = 1;
		for(int i = 1; i <= k; ++i){
			coef = coef * power(i, c[i]) % mod * fact[c[i]] % mod;
			if((c[i] + k) & 1) coef = mod-coef;
		}
		coef = power(coef, mod-2);
		poly P = {1};
		for(int i = 1; i <= k; ++i){
			if(c[i] == 0) continue;
			poly curr(i*c[i]+1);
			for(int j = 0; j <= c[i]; ++j){
				curr[i*j] = ncr[c[i]][j];
				if(j & 1) curr[i*j] = mod - curr[i*j];
			}
			P = P * curr;
		}
		P = inverse(P, exponents[0]+1);
		for(int e : exponents){
			coef = coef * P[e] % mod;
		}
		ans += coef;
		if(ans >= mod) ans -= mod;
	});
	cout << ans << "\n";
	return 0;
}