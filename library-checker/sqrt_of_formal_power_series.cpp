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

lli sqrtMod(lli a){
	a %= p;
	if(a < 0) a += p;
	if(a == 0) return 0;
	if(powerMod<p>(a, (p - 1) / 2) != 1) return -1;
	if(p % 4 == 3) return powerMod<p>(a, (p + 1) / 4);
	lli s = p - 1;
	int r = 0;
	while((s & 1) == 0) ++r, s >>= 1;
	lli n = 2;
	while(powerMod<p>(n, (p - 1) / 2) != p - 1) ++n;
	lli x = powerMod<p>(a, (s + 1) / 2);
	lli b = powerMod<p>(a, s);
	lli g = powerMod<p>(n, s);
	while(true){
		lli t = b;
		int m = 0;
		for(; m < r; ++m){
			if(t == 1) break;
			t = t * t % p;
		}
		if(m == 0) return x;
		lli gs = powerMod<p>(g, 1 << (r - m - 1));
		g = gs * gs % p;
		x = x * gs % p;
		b = b * g % p;
		r = m;
	}
}

const int inv2 = powerMod<p>(2, p - 2);

poly sqrtPolynomial(const poly & A){
	if(A.empty()) return {};
	int r0 = sqrtMod(A[0]); //verify that r0^2 = A[0] mod p
	if(r0 > p/2) r0 = (p - r0) % p;
	if(r0 == -1) return {-1};
	poly R(1, r0);
	//R(x) = R(x)/2 + A(x)/(2R(x))
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		poly a(min(c, A.size()));
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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	poly a(n);
	for(int& ai : a){
		cin >> ai;
	}
	int prefix_zeros = 0;
	for(int ai : a){
		if(ai == 0) prefix_zeros++;
		else break;
	}
	if(prefix_zeros == n){
		for(int i = 0; i < n; ++i){
			cout << "0 ";
		}
		cout << "\n";
	}else if(prefix_zeros%2 == 1){
		cout << "-1\n";
	}else{
		poly b;
		for(int i = prefix_zeros; i < n; ++i){
			b.push_back(a[i]);
		}
		b.resize(n - prefix_zeros/2);
		poly Sqrt = sqrtPolynomial(b);
		if(Sqrt.size() == 1 && Sqrt[0] == -1){
			cout << "-1\n";
		}else{
			for(int i = 0; i < prefix_zeros/2; ++i){
				cout << "0 ";
			}
			for(int ai : Sqrt){
				cout << ai << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}