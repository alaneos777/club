#include <bits/stdc++.h>
using namespace std;
typedef complex<double> comp;
typedef long long int lli;
double PI = acos(-1.0);

const int mod = 99991;
const int root5 = 10104;

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
	wlen_pw[0] = 1;
	for(len = 2; len <= n; len <<= 1){
		ang = inv == -1 ? -2 * PI / len : 2 * PI / len;
		len2 = len >> 1;
		comp wlen(cos(ang), sin(ang));
		for(i = 1; i < len2; ++i)
			wlen_pw[i] = wlen_pw[i - 1] * wlen;
		for(i = 0; i < n; i += len)
			for(j = 0; j < len2; ++j){
				t = X[i + j + len2] * wlen_pw[j];
				X[i + j + len2] = X[i + j] - t;
				X[i + j] += t;
			}
	}
	if(inv == -1)
		for(i = 0; i < n; ++i)
			X[i] /= n;
}

void conv(vector<int> & A, vector<int> & B){
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
	A.resize(sz);
	for(int i = 0, j = 0; i < sz; ++i){
		j = (size-1) & (size-i);
		lli p0 = (lli)round(real(c[i])) % mod;
		lli p1 = (lli)round(imag(c[i])) % mod;
		lli p2 = (lli)round(real(d[i])) % mod;
		A[i] = p0 + s*(p1 + p2*s % mod) % mod;
		while(A[i] >= mod) A[i] -= mod;
		while(A[i] < 0) A[i] += mod;
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

const int inv2 = inverse(2, mod);

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> conj(n);
	for(int & c : conj)
		cin >> c;
	int x = (lli)(1 + root5) * inv2 % mod;
	int y = (lli)(1 + mod - root5) * inv2 % mod;
	function<vector<int>(int, int, int)> mult = [&](int l, int r, int b){
		if(l == r) return vector<int>{(int)powerMod(b, conj[l], mod), 1};
		int m = (l + r) / 2;
		vector<int> left = mult(l, m, b);
		vector<int> right = mult(m+1, r, b);
		conv(left, right);
		return left;
	};
	int ans = (lli)(mult(0, n - 1, x)[n - k] - mult(0, n - 1, y)[n - k]) * inverse(root5, mod) % mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}