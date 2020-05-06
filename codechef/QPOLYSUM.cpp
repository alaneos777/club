#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli inverse(lli a, lli mod){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += mod;
	return s0;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

template<lli p, lli g>
void ntt(vector<lli> & X, int inv){
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
				lli u = X[i + j], v = X[i + j + k] * wp[j] % p;
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

template<lli p, lli g>
vector<lli> convolution(vector<lli> A, vector<lli> B){
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

lli mod, q;
string N;
vector<lli> eval, fact, inv, invfact;
int deg;

const lli a = 33706903339009ll, b = 33913061769217ll, c = 34187939676161ll;
const lli a_b = powerMod(a, b-2, b), a_c = powerMod(a, c-2, c), b_c = powerMod(b, c-2, c);
vector<lli> conv(const vector<lli> & A, const vector<lli> & B){
	vector<lli> P = convolution<a, 7>(A, B);
	vector<lli> Q = convolution<b, 5>(A, B);
	vector<lli> R = convolution<c, 3>(A, B);
	vector<lli> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		lli x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		lli x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		lli x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 % mod + a*(x2 + (lli)x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

vector<lli> inversePolynomial(const vector<lli> & A){
	vector<lli> R(1, inverse(A[0], mod));
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<lli> R2 = R;
		vector<lli> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = conv(R2, R2);
		R2.resize(c);
		R2 = conv(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += mod;
			if(R[i] >= mod) R[i] -= mod;
		}
	}
	R.resize(A.size());
	return R;
}

pair<vector<lli>, vector<lli>> sum(int l, int r){
	if(l > r) return {vector<lli>(), vector<lli>{1}};
	if(l == r) return make_pair(vector<lli>{eval[l] * invfact[l] % mod * invfact[deg-l] % mod * ((l&1) ? mod-1 : 1) % mod}, vector<lli>{-l + mod, 1});
	int m = (l + r) / 2;
	auto left = sum(l, m);
	auto right = sum(m+1, r);
	auto num1 = conv(left.first, right.second);
	auto num2 = conv(left.second, right.first);
	auto den = conv(left.second, right.second);
	for(int b = 0; b < num1.size(); ++b){
		num1[b] = (num1[b] + num2[b]) % mod;
	}
	return make_pair(num1, den);
}

vector<lli> interpolate(){
	vector<lli> num, den;
	tie(num, den) = sum(1, deg);
	vector<lli> lhs = conv(num, inversePolynomial(den));
	lhs.resize(deg+1);
	lhs.insert(lhs.begin(), eval[0] * invfact[deg] % mod);
	vector<lli> ans = conv(lhs, den);
	ans.resize(deg+1);
	if(deg & 1){
		for(lli & ai : ans){
			ai = (mod - ai) % mod;
		}
	}
	return ans;
}

vector<lli> exponential(){
	lli m1 = mod, m2 = 1;
	while(true){
		lli d = __gcd(m1, abs(q-1));
		if(d == 1) break;
		m1 /= d, m2 *= d;
	}
	vector<lli> num(deg+2), den(deg+2);
	lli n = 0;
	for(char c : N){
		n = (n * 10 % mod + (c - '0')) % mod;
	}
	lli qn = 1;
	for(char c : N){
		qn = powerMod(qn, 10, mod) * powerMod(q, c - '0', mod) % mod;
	}
	for(int i = 0; i <= deg+1; ++i){
		num[i] = powerMod(n, i, mod) * invfact[i] % mod * qn % mod;
		den[i] = invfact[i] * q % mod;
	}
	num[0]--, den[0]--;
	if(num[0] < 0) num[0] += mod;
	if(den[0] < 0) den[0] += mod;
	if(q == 1){
		num.erase(num.begin());
		den.erase(den.begin());
	}
	num.resize(deg+1);
	den.resize(deg+1);
	vector<lli> ans = conv(num, inversePolynomial(den));
	ans.resize(deg+1);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int64_t mod_, q_;
		cin >> mod_ >> q_ >> N >> deg;
		mod = mod_, q = q_;
		eval = vector<lli>(deg+1);
		fact = vector<lli>(deg+2, 1);
		inv = vector<lli>(deg+2, 1);
		invfact = vector<lli>(deg+2, 1);
		for(lli & ai : eval){
			int64_t ai_;
			cin >> ai_;
			ai = ai_;
		}
		for(int i = 1; i <= deg+1; ++i){
			fact[i] = fact[i-1] * i % mod;
			inv[i] = inverse(i, mod) % mod;
			invfact[i] = invfact[i-1] * inv[i] % mod;
		}
		vector<lli> c = interpolate();
		vector<lli> b = exponential();
		lli ans = 0;
		for(int j = 0; j <= deg; ++j){
			ans += c[j] * b[j] % mod * fact[j] % mod;
			if(ans >= mod) ans -= mod;
		}
		cout << (int64_t)ans << "\n";
	}
	return 0;
}