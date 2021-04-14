#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	is[1] = false;
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

auto is_sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return is;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	e %= m-1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

template<int p, int g>
void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, inv * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % p;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = powerMod(n, p - 2, p);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p;
	}
}

template<int p, int g>
vector<int> convolution(vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<p, g>(A, 1), ntt<p, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

const int p = 998244353, g = 3;

vector<int> operator+(const vector<int> & a, const vector<int> & b){
	vector<int> c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] = a[i];
		if(i < b.size()){
			c[i] += b[i];
			if(c[i] >= p) c[i] -= p;
		}
	}
	return c;
}

vector<int> operator-(const vector<int> & a, const vector<int> & b){
	vector<int> c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] = a[i];
		if(i < b.size()){
			c[i] -= b[i];
			if(c[i] < 0) c[i] += p;
		}
	}
	return c;
}

vector<int> operator*(vector<int> a, int k){
	for(int& ai : a){
		ai = ai * (lli)k % p;
	}
	return a;
}

vector<int> operator/(vector<int> a, int k){
	lli inv_k = powerMod(k, -1, p);
	for(int& ai : a){
		ai = ai * inv_k % p;
	}
	return a;
}

vector<int> shift(const vector<int>& a, int k){
	vector<int> b(a.size());
	for(int i = 0; k*i < a.size(); ++i){
		b[k*i] = a[i];
	}
	return b;
}

const int L = 500000;
const auto primes = sieve(L);
const auto is = is_sieve(L);

int ways(int n){
	if(n == 1 || n == 4 || n == 6) return -1;
	if(is[n]) return 1;
	if((n&1) == 0) return 2;
	if(is[n-2]) return 2;
	return 3;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(L+1, 1), inv(L+1, 1), invfact(L+1, 1);
	for(lli i = 2; i <= L; ++i){
		fact[i] = i * fact[i-1] % p;
		inv[i] = p - (p / i) * inv[p % i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	vector<int> P(L+1);
	for(int pr : primes){
		P[pr] = 1;
	}
	auto sq = convolution<p,g>(P, P);
	sq.resize(L+1);
	auto cb = convolution<p,g>(sq, P);
	cb.resize(L+1);
	auto tmp = convolution<p,g>(P, shift(P, 2));
	tmp.resize(L+1);
	auto two = (sq - shift(P, 2)) / 2;
	auto three = (cb - tmp*3 + shift(P, 3)*2) / 6;
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		if(ways(n) == -1){
			cout << "-1 -1\n";
		}else{
			int ans = 0;
			if(ways(n) == 1){
				ans = 1;
			}else if(ways(n) == 2){
				ans = two[n];
			}else{
				ans = three[n];
			}
			cout << ways(n) << " " << ans << "\n";
		}
	}
	return 0;
}