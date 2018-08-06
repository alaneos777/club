#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long int lli;
typedef complex<ld> comp;
ld PI = acosl(-1.0L);

int reverseBits(int n, int size){
	int ans = 0;
	while(size--){
		ans = (ans << 1) | (n & 1);
		n >>= 1;
	}
	return ans;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int nBits(int n){
	int ans = 0;
	while(n){
		n >>= 1;
		ans++;
	}
	return ans;
}

int mod(int a, int b){
	int r = a % b;
	if(r < 0) r += b;
	return r;
}

bool isZero(comp z){
	return abs(z.real()) < 1e-3;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	int log2n = nBits(n) - 1;
	comp w1 = polar(1.0L, 2.0 * PI / n);
	vector<comp> w(n);
	comp r;
	w[0] = 1;
	for(int i = 1; i < n; i++){
		w[i] = w[i - 1] * w1;
	}
	for(int i = 0; i < n; i++){
		int pos = reverseBits(i, log2n);
		if(i < pos) swap(X[i], X[pos]);
	}
	int pot = n >> 1, len = 1;
	for(int i = 0; i < log2n; i++){
		for(int j = 0; j < len; j++){
			for(int k = 0; k < pot; k++){
				int first = j + 2 * len * k, second = first + len;
				r = w[mod(pot * j * inv, n)] * X[second];
				X[second] = X[first] - r;
				X[first] += r;
			}
		}
		pot >>= 1, len <<= 1;
	}
	if(inv == -1){
		for(int i = 0; i < n; i++){
			X[i] /= n;
		}
	}
}

void quitar(vector<comp> & X){
	int l = X.size();
	for(int i = l - 1; i >= 0; i--){
		if(isZero(X[i])) X.pop_back();
		else break;
	}
	if(X.size() == 0) X.push_back(0);
}

void multiplyPolynomials(vector<comp> & A, vector<comp> & B){
	int degree = nearestPowerOfTwo(max(A.size(), B.size())) << 1;
	A.resize(degree);
	B.resize(degree);
	fft(A, 1);
	fft(B, 1);
	for(int i = 0; i < degree; i++){
		A[i] *= B[i];
	}
	fft(A, -1);
	quitar(A);
}

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	string s;
	while(n--){
		int sgn = 1;
		cin >> s;
		vector<comp> P(s.size());
		for(int i = s.size() - 1; i >= 0; i--){
			if(s[i] == '-') sgn *= -1;
			else P[s.size() - i - 1] = s[i] - '0';
		}
		cin >> s;
		vector<comp> Q(s.size());
		for(int i = s.size() - 1; i >= 0; i--){
			if(s[i] == '-') sgn *= -1;
			else Q[s.size() - i - 1] = s[i] - '0';
		}
		multiplyPolynomials(P, Q);
		vector<lli> coefs(P.size() + 1);
		for(int i = 0; i < P.size(); i++){
			lli coef = (lli)round(P[i].real());
			coefs[i] += coef;
			coefs[i + 1] = coefs[i] / 10;
			coefs[i] %= 10;
		}
		if(sgn == -1 && !(coefs.size() == 2 && coefs[0] == 0)) cout << "-";
		for(int i = coefs.size() - 1; i >= 0; i--){
			if(!(coefs.size() - 1 == i && coefs[i] == 0)) cout << coefs[i];
		}
		cout << "\n";
	}
	return 0;
}