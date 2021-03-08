#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;
const lli mod = lli(1e18) + 3;

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

struct SumPrimePi{
	int v;
	lli n;
	vector<lli> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		lli temp;
		for(p = 1; p <= v; p++){
			lo[p] = p - 1;
			hi[p] = n/p - 1;
		}
		for(p = 2; p <= v; p++){
			if(lo[p] == lo[p-1]) continue;
			primes.push_back(p);
			temp = lo[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v)
					hi[i] -= (hi[d] - temp);
				else
					hi[i] -= (lo[n/d] - temp);
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
			}
		}
	}

	lli get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

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

using poly = vector<lli>;

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

const lli N = 1e10;
const auto primes = sieve(sqrt(N));
auto pi = SumPrimePi(N);

map<pair<lli, lli>, lli> mem;
lli sum_primes(lli n, lli k, int idx = 0){
	if(idx == 0){
		if(mem.count({n, k})) return mem[{n, k}];
	}
	int lo = idx ? pi.primes[idx-1] : 0;
	lli ans = (pi.get(n) - pi.get(lo)) * k % mod;
	if(idx == 0) ans++;
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += power(k, e) * sum_primes(curr, k, i+1) % mod;
			if(ans >= mod) ans -= mod;
			ans += power(k, e+1);
			if(ans >= mod) ans -= mod;
			curr /= p;
			++e;
		}
	}
	if(idx == 0){
		mem[{n, k}] = ans;
	}
	return ans;
}

lli sum_powerful(lli n, const poly & g, int idx = 0){
	lli ans = (g[1] == 0 ? 1 : (g[1] == 1 ? n : sum_primes(n, g[1])));
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p*p);
		if(curr == 0) break;
		int e = 2;
		while(curr >= 1){
			lli term = g[e] - g[1]*g[e-1]%mod;
			if(term) ans += term * sum_powerful(curr, g, i+1) % mod;
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
			curr /= p;
			e++;
		}
	}
	return ans;
}

lli sum(lli n, const poly & g){
	//for(int i = 1; i < g.size(); ++i) cout << (int64_t)g[i] << ", "; cout << "\n";
	return sum_powerful(n, g);
}

int main(){
	pi.build();
	int k = log2l(N);

	vector<lli> fact(k+1, 1);
	for(lli i = 2; i <= k; ++i){
		fact[i] = i*fact[i-1] % mod;
	}

	vector<vector<lli>> ncr(k+1, vector<lli>(k+1));
	for(int i = 0; i <= k; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
		}
	}

	lli ans = 0;
	gen_partitions(k, [&](const vector<int> & part){
		vector<int> c(k+1);
		for(int p : part){
			c[p]++;
		}
		lli coef = 1;
		for(int i = 1; i <= k; ++i){
			coef = coef * power(i, c[i]) % mod * fact[c[i]] % mod;
		}
		coef = power(coef, mod-2);
		poly P = {1};
		for(int i = 1; i <= k; ++i){
			if(c[i] == 0) continue;
			poly curr(i*c[i]+1);
			for(int j = 0; j <= c[i]; ++j){
				curr[i*j] = ncr[c[i]][j];
			}
			P = P * curr;
		}
		P.resize(k+2);
		ans += coef * sum(N, P) % mod;
		if(ans >= mod) ans -= mod;
	});
	ans--;

	cout << (int64_t)ans << "\n";
	return 0;
}