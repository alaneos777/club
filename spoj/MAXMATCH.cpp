#include <bits/stdc++.h>
using namespace std;

const int p = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

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

void swapPositions(vector<int> & X){
	int n = X.size();
	int bit;
	for (int i = 1, j = 0; i < n; ++i) {
		bit = n >> 1;
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

void ntt(vector<int> & X, int inv) {
	int n = X.size();
	swapPositions(X);
	int len, len2, wlen, i, j, u, v, w;
	for (len = 2; len <= n; len <<= 1) {
		len2 = len >> 1;
		wlen = (inv == -1) ? root_1 : root;
		for (i = len; i < root_pw; i <<= 1){
			wlen = wlen * 1ll * wlen % p;
		}
		for (i = 0; i < n; i += len) {
			w = 1;
			for (j = 0; j < len2; ++j) {
				u = X[i + j], v = X[i + j + len2] * 1ll * w % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + len2] = u - v < 0 ? u - v + p : u - v;
				w = w * 1ll * wlen % p;
			}
		}
	}
	if (inv == -1) {
		int nrev = inverse(n, p);
		for (i = 0; i < n; ++i){
			X[i] = X[i] * 1ll * nrev % p;
		}
	}
}

void multiplyPolynomials(vector<int> & A, vector<int> & B){
	int degree = A.size() + B.size() - 2;
	int size = nearestPowerOfTwo(degree + 1);
	A.resize(size);
	B.resize(size);
	ntt(A, 1);
	ntt(B, 1);
	for(int i = 0; i < size; i++){
		A[i] = A[i] * 1ll * B[i] % p;
	}
	ntt(A, -1);
	A.resize(degree + 1);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	vector<int> ans(n);
	for(char c = 'a'; c <= 'c'; ++c){
		vector<int> P(n), Q(n);
		for(int i = 0; i < n; ++i){
			if(s[i] == c){
				P[i] = 1;
				Q[n - 1 - i] = 1;
			}
		}
		multiplyPolynomials(P, Q);
		for(int i = 0; i < n; ++i){
			ans[i] += P[n + i];
		}
	}
	int maximum = *max_element(ans.begin(), ans.end());
	cout << maximum << "\n";
	for(int i = 0; i < n; ++i){
		if(ans[i] == maximum) cout << i + 1 << " ";
	}
	return 0;
}