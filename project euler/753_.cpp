#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const int p = 754974721, g = 11;

vector<int> inversePolynomial(const vector<int> & A){
	vector<int> R(1, powerMod(A[0], p - 2, p));
	//R(x) = 2R(x)-A(x)R(x)^2
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<int> R2 = R;
		vector<int> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = convolution<p, g>(R2, R2);
		R2.resize(c);
		R2 = convolution<p, g>(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += p;
			if(R[i] >= p) R[i] -= p;
		}
	}
	R.resize(A.size());
	return R;
}

vector<int> derivative(vector<int> A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = (lli)A[i] * i % p;
	if(!A.empty()) A.erase(A.begin());
	return A;
}

vector<int> integral(vector<int> A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = (lli)A[i] * (powerMod(i+1, p-2, p)) % p;
	A.insert(A.begin(), 0);
	return A;
}

vector<int> logarithm(vector<int> A){
	assert(A[0] == 1);
	int n = A.size();
	A = convolution<p, g>(derivative(A), inversePolynomial(A));
	A.resize(n);
	A = integral(A);
	A.resize(n);
	return A;
}

vector<int> exponential(const vector<int> & A){
	assert(A[0] == 0);
	//E(x) = E(x)(1-ln(E(x))+A(x))
	vector<int> E(1, 1);
	while(E.size() < A.size()){
		size_t c = 2*E.size();
		E.resize(c);
		vector<int> S = logarithm(E);
		for(int i = 0; i < c && i < A.size(); ++i){
			S[i] = A[i] - S[i];
			if(S[i] < 0) S[i] += p;
		}
		S[0] = 1;
		E = convolution<p, g>(E, S);
		E.resize(c);
	}
	E.resize(A.size());
	return E;
}

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return primes;
}

const int M = 6e6;
const auto primes = sieve(M);

int main(){
	vector<int> inv(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		inv[i] = p - (p / i) * inv[p % i] % p;
	}
	vector<int> A((M-1)/3+1);
	for(int k = 1; k < A.size(); ++k){
		for(int j = 1; j*k < A.size(); ++j){
			int& pos = A[j*k];
			pos -= 2ll*inv[j]%p;
			if(pos < 0) pos += p;
		}
		for(int j = 1; 3*j*k < A.size(); ++j){
			int& pos = A[3*j*k];
			pos -= 2ll*inv[j]%p;
			if(pos < 0) pos += p;
		}
	}
	A = exponential(A);
	for(int& ai : A){
		if(ai > p/2) ai -= p;
	}
	lli ans = 0;
	for(int p : primes){
		if(p%3 == 1){
			ans += lli(p-1) * (p-8 - A[(p-1)/3]);
		}else{
			ans += lli(p-1) * (p-2);
		}
	}
	cout << ans << "\n";
	return 0;
}