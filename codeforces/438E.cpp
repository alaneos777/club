#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

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

const int p = 998244353;
const int root = 31;
const int root_1 = inverse(root, p);
const int root_pw = 1 << 23;

void ntt(vector<int> & X, int inv){
	int n = X.size();
	int len, len2, wlen, i, j, k, u, v, w;
	for(i = 1, j = 0; i < n - 1; ++i){
		for(k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(len = 2; len <= n; len <<= 1){
		len2 = len >> 1;
		wlen = (inv == -1) ? root_1 : root;
		for(i = len; i < root_pw; i <<= 1){
			wlen = (lli)wlen * wlen % p;
		}
		for(i = 0; i < n; i += len){
			w = 1;
			for(j = 0; j < len2; ++j){
				u = X[i + j], v = (lli)X[i + j + len2] * w % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + len2] = u - v < 0 ? u - v + p : u - v;
				w = (lli)w * wlen % p;
			}
		}
	}
	if(inv == -1){
		int nrev = inverse(n, p);
		for(i = 0; i < n; ++i){
			X[i] = (lli)X[i] * nrev % p;
		}
	}
}

vector<int> convolution(vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt(A, 1), ntt(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt(A, -1);
	A.resize(sz);
	return A;
}

vector<int> inversePolynomial(const vector<int> & A){
	vector<int> R(1, inverse(A[0], p));
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<int> R2 = R;
		vector<int> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = convolution(R2, R2);
		R2.resize(c);
		R2 = convolution(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += p;
			if(R[i] >= p) R[i] -= p;
		}
	}
	R.resize(A.size());
	return R;
}

const int inv2 = inverse(2, p);

vector<int> sqrtPolynomial(const vector<int> & A){
	int r0 = 1;
	vector<int> R(1, r0);
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<int> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		a = convolution(a, inversePolynomial(R));
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
	int n, m;
	cin >> n >> m;
	vector<int> c(n);
	for(int & ci : c){
		cin >> ci;
	}
	vector<int> C(*max_element(c.begin(), c.end()) + 1);
	for(int ci : c){
		C[ci] = p - 4;
	}
	C[0] = 1;
	m++;
	C.resize(m + 1);
	C = sqrtPolynomial(C);
	C[0]++;
	C = inversePolynomial(C);
	for(int i = 1; i < m; ++i){
		cout << (lli)2 * C[i] % p << "\n";
	}
	return 0;
}