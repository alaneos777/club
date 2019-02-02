#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = double;
using comp = complex<ld>;
ld PI = acosl(-1.0l);
const int mod = 786433;
const int g = 10;

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

void conv(vector<int> & A, vector<int> & B){
	int s = sqrt(mod);
	int size = B.size();
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
	for(int i = 0, j = 0; i < size; ++i){
		j = (size-1) & (size-i);
		lli p0 = (lli)round(real(c[i])) % mod;
		lli p1 = (lli)round(imag(c[i])) % mod;
		lli p2 = (lli)round(real(d[i])) % mod;
		A[i] = p0 + s*(p1 + p2*s % mod) % mod;
		while(A[i] >= mod) A[i] -= mod;
		while(A[i] < 0) A[i] += mod;
	}
}

void evaluate(vector<int> & x){
	int n = x.size();
	int m = nearestPowerOfTwo(2*n-1);
	int w = g, w1 = w, w2 = 1;
	vector<int> P(m), Q(m), b(n);
	for(int k = 0; k < n; ++k, w2 = (lli)w2*w1%mod, w1 = (lli)w1*w%mod*w%mod){
		b[k] = w2;
		P[k] = (lli)x[k] * b[k] % mod;
		Q[k] = inverse(b[k], mod);
		if(k) Q[m-k] = Q[k];
	}
	conv(P, Q);
	for(int k = 0; k < n; ++k){
		x[k] = (lli)b[k] * P[k] % mod;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//clock_t start = clock();
	int n, q, xi;
	cin >> n;
	vector<int> P(mod-1);
	for(int i = 0; i <= n; ++i){
		cin >> P[i];
	}
	int P0 = P[0];
	vector<int> pot(mod-1, 1), index(mod-1);
	for(int i = 1; i < mod-1; ++i){
		pot[i] = (lli)pot[i - 1] * g % mod;
	}
	for(int i = 0; i < mod-1; ++i){
		index[pot[i]] = i;
	}

	vector<int> even(P.size()), odd(P.size());
	for(int i = 0; i < P.size(); ++i){
		if(i & 1) odd[i/2] = P[i];
		else even[i/2] = P[i];
	}
	evaluate(odd);
	evaluate(even);
	for(int i = 0; i < P.size(); ++i){
		P[i] = even[i] + (lli)pot[i]*odd[i] % mod;
		while(P[i] >= mod) P[i] -= mod;
		while(P[i] < 0) P[i] += mod;
	}

	cin >> q;
	while(q--){
		cin >> xi;
		if(xi == 0) cout << P0 << "\n";
		else cout << P[index[xi]] << "\n";
	}
	//cout << fixed << setprecision(3) << (double)(clock() - start)/(double)CLOCKS_PER_SEC << "s\n";
	return 0;
}