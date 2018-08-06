#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

const lli m = 20092010;
const int n = 2000;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

const lli p = 23068673;
const lli root = 38;
const lli root_1 = 21247462;
const lli root_pw = 1 << 21;

lli inverse(lli a, lli n){
    lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
    while(r1){
        si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
        ri = r0 % r1, r0 = r1, r1 = ri;
    }
    if(s0 < 0) s0 += n;
    return s0;
}

void swapPositions(vector<lli> & X){
	int N = X.size();
	int bit;
	for (int i = 1, j = 0; i < N; ++i) {
		bit = N >> 1;
		while(j & bit){
			j ^= bit;
			bit >>= 1;
		}
		j ^= bit;
		if (i < j){
			swap (X[i], X[j]);
		}
	}
}

void ntt(vector<lli> & X, int inv) {
	int N = X.size();
	swapPositions(X);
	int len, len2, i, j;
	lli wlen, u, v, w;
	for (len = 2; len <= N; len <<= 1) {
		len2 = len >> 1;
		wlen = (inv == -1) ? root_1 : root;
		for (i = len; i < root_pw; i <<= 1){
			wlen = wlen * wlen % p;
		}
		for (i = 0; i < N; i += len) {
			w = 1;
			for (j = 0; j < len2; ++j) {
				u = X[i + j], v = X[i + j + len2] * w % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + len2] = u - v < 0 ? u - v + p : u - v;
				w = w * wlen % p;
			}
		}
	}
	if (inv == -1) {
		lli nrev = inverse(N, p);
		for (i = 0; i < N; ++i){
			X[i] = X[i] * nrev % p;
		}
	}
}

void multiplyPolynomials(vector<lli> & A, vector<lli> & B){
	int degree = A.size() + B.size() - 2;
	int size = nearestPowerOfTwo(degree + 1);
	A.resize(size);
	B.resize(size);
	ntt(A, 1);
	ntt(B, 1);
	for(int i = 0; i < size; i++){
		A[i] = A[i] * B[i] % p;
	}
	ntt(A, -1);
	A.resize(degree + 1);
}

vector<lli> mult(vector<lli> P, vector<lli> Q){
	multiplyPolynomials(P, Q);
	for(int i = 0; i < n; ++i){
		if(i < n - 1) P[i] += P[i + n];
		if(i > 0) P[i] += P[i + n - 1];
	}
	for(int i = 0; i < n; ++i){
		P[i] %= m;
	}
	P.resize(n);
	return P;
}

int main(){
	lli k = 1e18;

	vector<lli> coefAns(n), coefTmp(n);
	coefAns[0] = 1;
	coefTmp[1] = 1;
	while(k){
		if(k & 1) coefAns = mult(coefAns, coefTmp);
		k >>= 1;
		if(k) coefTmp = mult(coefTmp, coefTmp);
	}

	lli F = 0;
	for(int i = 0; i < n; ++i){
		F += coefAns[i];
	}
	F %= m;
	cout << F << "\n";

	return 0;
}