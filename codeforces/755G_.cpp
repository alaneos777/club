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

const int p = 998244353, g = 3;

vector<int> inversePolynomial(const vector<int> & A){
	vector<int> R(1, powerMod(A[0], p - 2, p));
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

const lli inv2 = powerMod(2, p - 2, p);

vector<int> sqrtPolynomial(const vector<int> & A){
	int r0 = 1;
	vector<int> R(1, r0);
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<int> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		a = convolution<p, g>(a, inversePolynomial(R));
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + a[i];
			if(R[i] >= p) R[i] -= p;
			R[i] = (lli)R[i] * inv2 % p;
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

vector<int> power(const vector<int>& a, lli n){
	int t = 0;
	for(int i = 0; i < a.size(); ++i){
		if(a[i] != 0){
			t = i;
			break;
		}
	}
	lli lead = powerMod(a[t], n, p);
	lli inv_lead = powerMod(a[t], -1, p);
	vector<int> b, c(a.size());
	for(int i = t; i < a.size(); ++i){
		b.push_back(inv_lead * a[i] % p);
	}
	b = logarithm(b);
	for(int& bi : b){
		bi = (n % p) * bi % p;
	}
	b = exponential(b);
	for(int i = 0; i + n*t < b.size(); ++i){
		c[i + n*t] = lead * b[i] % p;
	}
	return c;
}

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

vector<int> operator/(vector<int> a, int k){
	lli inv_k = powerMod(k, -1, p);
	for(int& ai : a){
		ai = ai * inv_k % p;
	}
	return a;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	int k;
	cin >> n >> k;
	vector<int> R = {1, 6, 1};
	R.resize(k+1);
	R = sqrtPolynomial(R);
	vector<int> z1 = (vector<int>{1, 1} + R) / 2, z2 = (vector<int>{1, 1} - R) / 2;
	vector<int> c1 = convolution<p,g>(vector<int>{1, 1} - z2, inversePolynomial(R));
	c1.resize(k+1);
	vector<int> c2 = vector<int>{1} - c1;
	vector<int> ans = convolution<p,g>(c1, power(z1, n)) + convolution<p,g>(c2, power(z2, n));
	ans.resize(k+1);
	for(int i = 1; i <= k; ++i){
		if(i > 1) cout << " ";
		cout << ans[i];
	}
	cout << "\n";
	return 0;
}