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

using poly = vector<int>;

poly operator*(const poly & b, const poly & a){
	poly c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		if(a[i] == 0) continue;
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

using part = vector<vector<int>>;

poly gen(int a){
	poly curr(a+1);
	curr[0] = 1, curr[a] = mod-1;
	return curr;
}

void gen_set_partitions(int n, function<void(const part& pi)> f){
	queue<part> q;
	q.push({{0}});
	if(n == 1) f({{0}});
	for(int i = 1; i < n; ++i){
		int sz = q.size();
		while(sz--){
			auto pi = q.front();
			q.pop();
			for(auto& eq : pi){
				eq.push_back(i);
				if(i == n-1) f(pi);
				if(i != n-1) q.push(pi);
				eq.pop_back();
			}
			pi.push_back({i});
			if(i == n-1) f(pi);
			if(i != n-1) q.push(pi);
		}
	}
}

int lcm(int a, int b){
	return a / __gcd(a, b) * b;
}

auto divsSieve(int n){
	vector<vector<int>> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j].push_back(i);
		}
	}
	return divs;
}

const auto divs = divsSieve(100);

int main(){
	int N = 1e6;
	vector<int> parts = {1, 2, 3, 4};

	vector<int> coefs;
	for(int p : parts){
		for(int i = 1; i <= p; ++i){
			coefs.push_back(p);
		}
	}
	int k = coefs.size();
	int mx = accumulate(coefs.begin(), coefs.end(), 0);

	vector<int> fact(100000+1, 1);
	for(lli i = 2; i <= 100000; ++i){
		fact[i] = i*fact[i-1] % mod;
	}
	vector<vector<int>> ncr(mx+1, vector<int>(mx+1));
	for(int i = 0; i <= mx; ++i){
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

	map<vector<int>, int> freq;
	gen_set_partitions(k, [&](const auto& pi){
		lli coef = 1;
		vector<int> c(mx+1);
		for(const auto& eq : pi){
			coef = coef * fact[eq.size()-1] % mod;
			if((eq.size() & 1) == 0) coef = mod-coef;
			int sum = 0;
			for(int x : eq){
				sum += coefs[x];
			}
			c[sum]++;
		}
		(freq[c] += coef) %= mod;
	});

	lli ans = 0;
	int cr = 0;
	for(const auto&[c, cnt] : freq){
		lli coef = cnt;
		poly P = {1};
		set<int> st;
		int cycle_len = 1;
		vector<int> cnt_unity(mx+1);
		for(int i = 1; i <= mx; ++i){
			if(c[i] == 0) continue;
			cycle_len = lcm(cycle_len, i);
			for(int d : divs[i]){
				cnt_unity[d] += c[i];
			}
			poly curr(i*c[i]+1);
			for(int j = 0; j <= c[i]; ++j){
				curr[i*j] = ncr[c[i]][j];
				if(j & 1) curr[i*j] = mod - curr[i*j];
			}
			P = P * curr;
		}
		int degree = *max_element(cnt_unity.begin(), cnt_unity.end());
		int sz = (degree+1)*cycle_len;
		poly init = inverse(P, sz);
		vector<poly> Q(cycle_len, poly(degree+1));
		for(int i = 0; i < sz; ++i){
			Q[i%cycle_len][i/cycle_len] = init[i];
		}
		for(int e : exponents){
			lli eval = 0;
			int idx = e%cycle_len;
			e /= cycle_len;
			if(e <= degree) eval = Q[idx][e];
			else{
				lli alt = 1;
				for(int i = 0; i <= degree; ++i){
					int den = lli(e-i) * fact[i] % mod * fact[degree-i] % mod;
					eval += Q[idx][i] * alt % mod * power(den, mod-2) % mod;
					if(eval >= mod) eval -= mod;
					alt = mod-alt;
				}
				for(int i = 0; i <= degree; ++i){
					eval = eval * (e-i) % mod;
				}
				if(degree & 1) eval = (mod-eval) % mod;
			}
			coef = coef * eval % mod;
		}
		ans += coef;
		if(ans >= mod) ans -= mod;
	}

	for(int p : parts){
		ans = ans * power(fact[p], mod-2) % mod;
	}

	cout << ans << "\n";
	return 0;
}