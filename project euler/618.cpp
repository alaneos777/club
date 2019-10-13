#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<bool> isPrime(n+1, true);
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const lli mod = 1e9;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int inverse(int a, int n){
	int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
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

template<int prime, int gen>
void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(gen, inv * (prime - 1) / (k<<1), prime);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % prime;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % prime;
				X[i + j] = u + v < prime ? u + v : u + v - prime;
				X[i + j + k] = u - v < 0 ? u - v + prime : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = inverse(n, prime);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % prime;
	}
}

template<int prime, int gen>
vector<int> convolution(vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<prime, gen>(A, 1), ntt<prime, gen>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % prime;
	ntt<prime, gen>(A, -1);
	A.resize(sz);
	return A;
}

const int a = 998244353, b = 985661441, c = 754974721;
const lli a_b = inverse(a, b), a_c = inverse(a, c), b_c = inverse(b, c);
vector<int> conv(const vector<int> & A, const vector<int> & B){
	vector<int> P = convolution<a, 3>(A, B);
	vector<int> Q = convolution<b, 3>(A, B);
	vector<int> R = convolution<c, 11>(A, B);
	vector<int> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		int x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		int x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		int x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 + a*(x2 + (lli)x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

vector<int> inversePolynomial(const vector<int> & A){
	vector<int> R(1, inverse(A[0], mod));
	//R(x) = 2R(x)-A(x)R(x)^2
	while(R.size() < A.size()){
		vector<int> TR = conv(A, conv(R, R));
		int c = 2*R.size();
		R.resize(c);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - TR[i];
			if(R[i] < 0) R[i] += mod;
			if(R[i] >= mod) R[i] -= mod;
		}
	}
	R.resize(A.size());
	return R;
}

int main(){
	int limit = 24;
	vector<int> F(limit + 1);
	F[1] = 1;
	for(int i = 2; i <= limit; ++i){
		F[i] = F[i-1] + F[i-2];
	}
	vector<int> primes = sieve(F[limit]);
	unordered_map<int, lli> poly;
	poly[0] = 1;
	for(int p : primes){
		auto tmp = poly;
		for(auto par : tmp){
			if(par.first + p <= F[limit]){
				poly[par.first + p] += (lli)par.second * (mod - p) % mod;
				if(poly[par.first + p] >= mod) poly[par.first + p] -= mod;
			}
		}
	}
	vector<int> P(F[limit] + 1);
	for(auto par : poly){
		P[par.first] = par.second;
	}
	P = inversePolynomial(P);
	int ans = 0;
	for(int i = 2; i <= limit; ++i){
		ans += P[F[i]];
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}