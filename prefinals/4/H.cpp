#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using comp = complex<ld>;
const ld PI = acos(-1.0);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<comp> wp(n>>1);
	for(int k = 1; k < n; k <<= 1){
		for(int j = 0; j < k; ++j)
			wp[j] = polar(1.0l, PI * j / k * inv);
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				comp t = X[i + j + k] * wp[j];
				X[i + j + k] = X[i + j] - t;
				X[i + j] += t;
			}
		}
	}
	if(inv == -1)
		for(int i = 0; i < n; ++i)
			X[i] /= n;
}

void sq(vector<comp> & P){
	int sz = 2*P.size() - 1;
	int size = nearestPowerOfTwo(sz);
	P.resize(size);
	fft(P, 1);
	for(int i = 0; i < size; ++i){
		P[i] *= P[i];
	}
	fft(P, -1);
	P.resize(sz);
	for(comp & x : P){
		x.imag(0);
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int h = 4*log2(n) + 1;
	vector<comp> P(n+1);
	P[0] = 1;
	ld prev = P[n].real();
	for(int i = 1; i <= h && i <= n; ++i){
		sq(P);
		P.insert(P.begin(), 1);
		if(P.size() > n+1) P.resize(n+1);
		for(int j = 1; j < P.size(); ++j){
			P[j] /= j;
		}
		cout << fixed << setprecision(8) << (P[n].real() - prev) << "\n";
		prev = P[n].real();
	}
	for(int i = min(h, n) + 1; i <= n; ++i){
		cout << "0\n";
	}
	return 0;
}