#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = double;
using comp = complex<ld>;
const ld PI = acosl(-1);

lli mod = 1e9 + 7;

inline lli modula(lli x){
	while(x >= mod) x -= mod;
	while(x < 0) x += mod;
	return x;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	int len, len2, i, j, k;
	for(i = 1, j = 0; i < n - 1; ++i){
		for(k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	ld ang;
	comp t, u, v;
	vector<comp> wlen_pw(n >> 1);
	for(len = 2; len <= n; len <<= 1){
		ang = inv == -1 ? -2 * PI / len : 2 * PI / len;
		len2 = len >> 1;
		for(i = 0; i < len2; ++i){
			wlen_pw[i] = comp(cos(ang*i), sin(ang*i));
		}
		for(i = 0; i < n; i += len){
			for(j = 0; j < len2; ++j){
				t = X[i + j + len2] * wlen_pw[j];
				X[i + j + len2] = X[i + j] - t;
				X[i + j] += t;
			}
		}
	}
	if(inv == -1){
		for(i = 0; i < n; ++i){
			X[i] /= n;
		}
	}
}

vector<lli> conv(vector<lli> A, const vector<lli> & B){
	lli s = sqrt(mod);
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	vector<comp> a(size), b(size);
	for(int i = 0; i < A.size(); ++i){
		a[i] = comp(A[i] % s, A[i] / s);
	}
	for(int i = 0; i < B.size(); ++i){
		b[i] = comp(B[i] % s, B[i] / s);
	}
	fft(a, 1);
	fft(b, 1);
	comp I(0, 1);
	vector<comp> c(size), d(size);
	for(int i = 0, j = 0; i < size; ++i){
		j = (size-1) & (size-i);
		comp e = (a[i] + conj(a[j])) * 0.5;
		comp f = (conj(a[j]) - a[i]) * 0.5 * I;
		comp g = (b[i] + conj(b[j])) * 0.5;
		comp h = (conj(b[j]) - b[i]) * 0.5 * I;
		c[i] = e * g + I * (e * h + f * g);
		d[i] = f * h;
	}
	fft(c, -1);
	fft(d, -1);
	A.resize(sz);
	for(int i = 0, j = 0; i < sz; ++i){
		j = (size-1) & (size-i);
		lli p0 = (lli)round(real(c[i])) % mod;
		lli p1 = (lli)round(imag(c[i])) % mod;
		lli p2 = (lli)round(real(d[i])) % mod;
		A[i] = modula(p0 + s*(p1 + p2*s % mod) % mod);
	}
	return A;
}

vector<lli> inversePolynomial(const vector<lli> & A){
	vector<lli> R(1, inverse(A[0], mod));
	while(R.size() < A.size()){
		int c = 2 * R.size();
		R.resize(c);
		vector<lli> TR = R;
		TR.resize(nearestPowerOfTwo(2 * c));
		vector<lli> TF(TR.size());
		for(int i = 0; i < c && i < A.size(); ++i){
			TF[i] = A[i];
		}
		TR = conv(conv(TR, TR), TF);
		for(int i = 0; i < c; ++i){
			R[i] = modula(R[i] + R[i] - TR[i]);
		}
	}
	R.resize(A.size());
	return R;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

vector<lli> solve(int n, int k, lli t, const vector<lli> & a){
	int L = k + 10;
	vector<lli> fact(L + 1, 1), invfact(L + 1, 1), expo(L);
	for(int i = 1; i <= L; ++i){
		fact[i] = fact[i - 1] * i % mod;
		invfact[i] = inverse(fact[i], mod);
	}
	for(int i = 0; i < L; ++i){
		expo[i] = invfact[i + 1];
		if(i & 1) expo[i] = modula(-expo[i]);
	}
	vector<lli> bernoulli = inversePolynomial(expo);
	for(int i = 0; i < L; ++i){
		bernoulli[i] = bernoulli[i] * fact[i] % mod;
	}

	vector<lli> r(k + 1), s(k + 1);
	for(int j = 0; j <= k; ++j){
		r[j] = bernoulli[j] * invfact[j] % mod;
		s[j] = powerMod(t, j + 1, mod) * invfact[j + 1] % mod;
	}
	vector<lli> P = conv(r, s);
	P.resize(k + 1);
	P[0] = modula(P[0] + 1);

	function<pair<vector<lli>, vector<lli>>(int, int)> invert = [&](int i, int j){
		if(i == j) return make_pair(vector<lli>{1}, vector<lli>{1, modula(-a[i])});
		int m = (i + j) / 2;
		auto left = invert(i, m);
		auto right = invert(m + 1, j);
		auto num1 = conv(left.first, right.second);
		auto num2 = conv(left.second, right.first);
		auto den = conv(left.second, right.second);
		for(int b = 0; b < num1.size(); ++b){
			num1[b] = modula(num1[b] + num2[b]);
		}
		return make_pair(num1, den);
	};

	vector<lli> num, den;
	tie(num, den) = invert(0, n - 1);
	num.resize(k + 1); den.resize(k + 1);
	vector<lli> Q = conv(num, inversePolynomial(den));
	Q.resize(k + 1);
	for(int l = 0; l <= k; ++l){
		Q[l] = Q[l] * invfact[l] % mod;
	}

	vector<lli> G = conv(P, Q);
	G.resize(k + 1);
	for(int i = 0; i <= k; ++i){
		G[i] = G[i] * fact[i] % mod;
	}
	return G;
}

int main(){
	//clock_t start = clock();
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k; lli t;
	cin >> n >> k >> t;
	vector<lli> arr(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
	}

	vector<lli> G = solve(n, k, t % mod, arr);
	for(int i = 0; i < G.size(); ++i){
		if(i) cout << " ";
		cout << G[i];
	}
	cout << "\n";
	//cout << (double)(clock()-start)/(double)CLOCKS_PER_SEC << "\n";
	return 0;
}