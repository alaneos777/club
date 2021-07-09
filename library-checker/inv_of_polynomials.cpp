#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using poly = vector<int>;

template<lli mod>
lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

template<int mod, int g>
void ntt(poly& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n-1; ++i){
		for(int k = n>>1; (j^=k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz <<= 1){
		lli w_1 = powerMod<mod>(g, (mod-1)/sz);
		if(inv == -1) w_1 = powerMod<mod>(w_1, mod-2);
		vector<lli> w(sz/2, 1);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w_1 * w[j-1] % mod;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = w[j] * a[start + sz/2 + j] % mod;
				a[start + j] = (u+v >= mod ? u+v-mod : u+v);
				a[start + sz/2 + j] = (u-v < 0 ? u-v+mod : u-v);
			}
		}
	}
	if(inv == -1){
		lli n_rev = powerMod<mod>(n, mod-2);
		for(int& ai : a){
			ai = ai * n_rev % mod;
		}
	}
}

template<int mod, int g>
poly convolution(poly a, poly b){
	int sz = a.size() + b.size() - 1;
	if(sz <= 256){
		vector<int> c(a.size() + b.size() - 1);
		for(int i = 0; i < a.size(); ++i){
			for(int j = 0; j < b.size(); ++j){
				c[i+j] = (c[i+j] + (lli)a[i]*b[j]) % mod;
			}
		}
		return c;
	}
	int SZ = nearestPowerOfTwo(sz);
	a.resize(SZ), b.resize(SZ);
	ntt<mod, g>(a, 1), ntt<mod, g>(b, 1);
	poly c(SZ);
	for(int i = 0; i < SZ; ++i){
		c[i] = (lli)a[i] * b[i] % mod;
	}
	ntt<mod, g>(c, -1);
	c.resize(sz);
	return c;
}

const int p = 998244353, g = 3;

poly inversePolynomial(const poly & A){
	poly R(1, powerMod<p>(A[0], p - 2));
	//R(x) = 2R(x)-A(x)R(x)^2
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		poly R2 = R;
		poly a(min(c, A.size()));
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

poly quotient(poly A, poly B){
	int n = A.size(), m = B.size();
	if(n < m) return poly{0};
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(n-m+1), B.resize(n-m+1);
	A = convolution<p, g>(A, inversePolynomial(B));
	A.resize(n-m+1);
	reverse(A.begin(), A.end());
	return A;
}

void clean(poly& A){
	while(!A.empty() && A.back() == 0) A.pop_back();
}

poly operator+(const poly& a, const poly& b){
	poly c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] = a[i];
		if(i < b.size()) c[i] += b[i];
		if(c[i] >= p) c[i] -= p;
	}
	clean(c);
	return c;
}

poly operator-(const poly& a, const poly& b){
	poly c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		if(i < a.size()) c[i] = a[i];
		if(i < b.size()) c[i] -= b[i];
		if(c[i] < 0) c[i] += p;
	}
	clean(c);
	return c;
}

const poly zero, one = {1};
poly operator*(const poly& a, const poly& b){
	if(a.empty() || b.empty()) return {};
	poly ans = convolution<p,g>(a, b);
	clean(ans);
	return ans;
}

using mat = array<poly, 4>;
using arr = array<poly, 2>;
mat operator*(const mat& A, const mat& B){
	return {A[0]*B[0] + A[1]*B[2], A[0]*B[1] + A[1]*B[3], A[2]*B[0] + A[3]*B[2], A[2]*B[1] + A[3]*B[3]};
}

arr operator*(const mat& A, const arr& b){
	return {A[0]*b[0] + A[1]*b[1], A[2]*b[0] + A[3]*b[1]};
}

mat pgcd(arr a){
	assert(a[0].size() > a[1].size() && !a[1].empty());
	int m = a[0].size()/2;
	if(a[1].size() <= m) return {one, zero, zero, one};
	auto R = pgcd({poly(a[0].begin() + m, a[0].end()), poly(a[1].begin() + m, a[1].end())});
	a = R*a;
	if(a[1].size() <= m) return R;
	mat Q = {zero, one, one, zero - quotient(a[0], a[1])};
	R = Q*R, a = Q*a;
	if(a[1].size() <= m) return R;
	int k = 2*m + 1 - a[0].size();
	return pgcd({poly(a[0].begin() + k, a[0].end()), poly(a[1].begin() + k, a[1].end())}) * R;
}

mat egcd(arr a){
	assert(a[0].size() > a[1].size() && !a[1].empty());
	auto m0 = pgcd(a);
	a = m0*a;
	if(a[1].empty()) return m0;
	mat Q = {zero, one, one, zero - quotient(a[0], a[1])};
	m0 = Q*m0, a = Q*a;
	if(a[1].empty()) return m0;
	return egcd(a) * m0;
}

array<poly, 3> extgcd(const poly& a, const poly& b){
	mat Q = {zero, one, one, zero - quotient(a, b)};
	auto m = Q;
	auto ap = Q*arr{a, b};
	if(!ap[1].empty()) m = egcd(ap) * m;
	return {a*m[0] + b*m[1], m[0], m[1]};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	poly A(n), B(m);
	for(int& ai : A){
		cin >> ai;
	}
	for(int& bi : B){
		cin >> bi;
	}
	auto[d, x, y] = extgcd(A, B);
	if(d.size() > 1){
		cout << "-1\n";
	}else{
		lli inv = powerMod<p>(d[0], p-2);
		cout << x.size() << "\n";
		for(int i = 0; i < x.size(); ++i){
			cout << x[i]*inv % p << " ";
		}
		if(x.size()) cout << "\n";
	}
	return 0;
}