#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using comp = complex<double>;
const double PI = acos(-1.0);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	int len, len2, i, j, k;
	for(i = 1, j = 0; i < n - 1; ++i){
		for(k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	double ang;
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

int inverse(int a, int n){
	int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

const int mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<int> conv(const vector<int> & A, const vector<int> & B){
	int s = sqrt(mod);
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	vector<comp> a(size), b(size);
	for(int i = 0; i < A.size(); ++i)
		a[i] = comp(A[i] % s, A[i] / s);
	for(int i = 0; i < B.size(); ++i)
		b[i] = comp(B[i] % s, B[i] / s);
	fft(a, 1), fft(b, 1);
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
	fft(c, -1), fft(d, -1);
	vector<int> D(sz);
	for(int i = 0, j = 0; i < sz; ++i){
		j = (size-1) & (size-i);
		int p0 = (lli)round(real(c[i])) % mod;
		int p1 = (lli)round(imag(c[i])) % mod;
		int p2 = (lli)round(real(d[i])) % mod;
		D[i] = p0 + s*(p1 + (lli)p2*s % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

const int M = 1e6 + 100;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
	for(int i = 2; i <= M; ++i){
		fact[i] = (lli)fact[i-1] * i % mod;
		inv[i] = mod - (lli)(mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)invfact[i-1] * inv[i] % mod;
	}
	int t, n, x, r;
	cin >> t;
	while(t--){
		cin >> n >> x >> r;
		vector<int> p(r), q(r);
		for(int i = 0; i < r; ++i){
			p[i] = powerMod(i, r) * invfact[i] % mod;
			q[i] = invfact[i];
			if(i & 1) q[i] = (mod - q[i]) % mod;
		}
		vector<int> stirling = (r == 0 ? vector<int>{} : conv(p, q));
		stirling.resize(r);
		stirling.push_back(1);

		p = vector<int>(r+1), q = vector<int>(r+1);
		int comb = 1;
		for(int i = 0; i <= r; ++i){
			p[i] = (lli)comb * powerMod(x, n+1-i) % mod;
			q[i] = powerMod(x-1, -i-1);
			if(i & 1) q[i] = (mod - q[i]) % mod;
			comb = (lli)comb * (n+1-i) % mod * inv[i+1] % mod;
		}
		vector<int> f = conv(p, q);
		f.resize(r+1);
		for(int j = 0; j <= r; ++j){
			f[j] = (lli)f[j] * fact[j] % mod;
			int term = (lli)fact[j] * powerMod(x-1, -j-1) % mod;
			if(!(j & 1)) term = (mod - term) % mod;
			f[j] += term;
			if(f[j] >= mod) f[j] -= mod;
		}
		int ans = 0, x_pw = 1;
		for(int i = 0; i <= r; ++i){
			ans += (lli)stirling[i] * x_pw % mod * f[i] % mod;
			if(ans >= mod) ans -= mod;
			x_pw = (lli)x_pw * x % mod;
		}
		if(r == 0) ans = (ans + mod-1) % mod;
		cout << ans << "\n";
	}
	return 0;
}