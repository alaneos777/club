#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef vector<lli> vi;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int p = 998244353, root = 31, root_1 = 128805723, root_pw = 1 << 23;

int inverse(int a, int n){
	int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

void ntt(vi & X, int inv){
	int n = X.size(), i, j, k, len, len2, wlen, u, v, w;
	if(inv == 1) n = nearestPowerOfTwo(2 * n - 1), X.resize(n);
	for(i = 1, j = 0; i < n - 1; ++i){
		for (k = n >> 1; (j ^= k) < k; k >>= 1);
		if (i < j) swap(X[i], X[j]);
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
		for(i = 0; i < n; ++i) X[i] = (lli)X[i] * nrev % p;
	}
}

int degree;

vi multiplyPolynomials(vi A, vi & B){
	for(int i = 0; i < A.size(); ++i) A[i] = (lli)A[i] * B[i] % p;
	ntt(A, -1);
	A.resize(degree + 1);
	return A;
}

void sum(vi & a, vi & b){
	for(int i = 0; i <= degree; ++i){
		a[i] += b[i];
		while(a[i] >= p) a[i] -= p;
	}
}

vi c1, c0;
void mult(vi & a1, vi & a0, vi b1, vi b0, bool diff){
	vi c1_, c2;
	if(diff){
		ntt(a1, 1);
		ntt(a0, 1);
		ntt(b1, 1);
		ntt(b0, 1);
		c0 = multiplyPolynomials(a0, b0);
		c1 = multiplyPolynomials(a0, b1);
		c1_ = multiplyPolynomials(a1, b0);
		c2 = multiplyPolynomials(a1, b1);
	}else{
		ntt(a1, 1);
		ntt(a0, 1);
		c0 = multiplyPolynomials(a0, a0);
		c1 = multiplyPolynomials(a0, a1);
		c1_ = c1;
		c2 = multiplyPolynomials(a1, a1);
	}
	sum(c1, c1_);
	for(int i = 0; i <= degree; ++i){
		if(i != degree) c0[i+1] += c2[i];
		if(i != degree) c1[i+1] += c2[i];
		c1[i] += c2[i];
		while(c0[i] >= p) c0[i] -= p;
		while(c1[i] >= p) c1[i] -= p;
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, k;
	cin >> n >> k;
	degree = min(n, k);
	vi DP0(degree+1); DP0[0] = 1;
	vi DP1(degree+1); DP1[0] = DP1[1] = 1;
	vi ans0(degree+1); ans0[0] = 1;
	vi ans1(degree+1);
	vi tmp1(degree+1); tmp1[0] = 1;
	vi tmp0(degree+1);
	while(n){
		if(n & 1){
			mult(ans1, ans0, tmp1, tmp0, true);
			ans1 = c1;
			ans0 = c0;
		}
		n >>= 1;
		if(n){
			mult(tmp1, tmp0, tmp1, tmp0, false);
			tmp1 = c1;
			tmp0 = c0;
		}
	}
	ans1.resize(k + 1);
	ans0.resize(k + 1);
	vi DPn(k + 1);
	for(int i = 0; i <= k; ++i){
		DPn[i] += ans1[i] + ans0[i];
		if(i != k) DPn[i+1] += ans1[i];
		while(DPn[i] >= p) DPn[i] -= p;
	}
	for(int i = 1; i <= k; ++i){
		if(i != 1) cout << " ";
		cout << DPn[i];
	}
	cout << "\n";
	return 0;
}