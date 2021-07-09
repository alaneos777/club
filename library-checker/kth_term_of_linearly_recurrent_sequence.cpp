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

//returns Q(x), where A(x)=B(x)Q(x)+R(x)
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

//returns R(x), where A(x)=B(x)Q(x)+R(x)
poly remainder(poly A, const poly & B){
	int n = A.size(), m = B.size();
	if(n >= m){
		poly C = convolution<p, g>(quotient(A, B), B);
		A.resize(m-1);
		for(int i = 0; i < m-1; ++i){
			A[i] -= C[i];
			if(A[i] < 0) A[i] += p;
		}
	}
	return A;
}

lli rec(const vector<int> & P, const vector<int> & init, lli n){
	int deg = (int)P.size()-1;
	vector<int> ans(deg);
	ans[0] = 1;
	lli pot = 1;
	for(lli v = n; v >>= 1; pot <<= 1);
	do{
		int d = (n & pot) != 0;
		ans = convolution<p,g>(ans, ans);
		if(d == 1) ans.insert(ans.begin(), 0);
		ans = remainder(ans, P);
	}while(pot >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += (lli)ans[i] * init[i]) %= p;
	return nValue;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int d; lli n;
	cin >> d >> n;
	vector<int> init(d), poly(d);
	for(int& ii : init){
		cin >> ii;
	}
	for(int& di : poly){
		cin >> di;
		di = (p - di) % p;
	}
	reverse(poly.begin(), poly.end());
	poly.push_back(1);
	cout << rec(poly, init, n) << "\n";
	return 0;
}