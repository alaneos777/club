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
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(int k = 1; k < n; k <<= 1){
		int wlen = (inv == -1) ? root_1 : root;
		for(int i = k << 1; i < root_pw; i <<= 1)
			wlen = (lli)wlen * wlen % p;
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0, w = 1; j < k; ++j, w = (lli)w * wlen % p){
				int u = X[i + j], v = (lli)X[i + j + k] * w % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
	}
	if(inv == -1){
		int nrev = inverse(n, p);
		for(int i = 0; i < n; ++i)
			X[i] = (lli)X[i] * nrev % p;
	}
}

inline int modula(int x){
	while(x >= p) x -= p;
	while(x < 0) x += p;
	return x;
}

vector<int> conv(vector<int> A, vector<int> B){
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
		int c = 2 * R.size();
		R.resize(c);
		vector<int> TR = R;
		TR.resize(2 * c);
		vector<int> TF(TR.size());
		for(int i = 0; i < c && i < A.size(); ++i)
			TF[i] = A[i];
		ntt(TR, 1);
		ntt(TF, 1);
		for(int i = 0; i < TR.size(); ++i)
			TR[i] = (lli)TR[i] * TR[i] % p * TF[i] % p;
		ntt(TR, -1);
		for(int i = 0; i < c; ++i){
			R[i] = modula(R[i] + R[i] - TR[i]);
		}
	}
	R.resize(A.size());
	return R;
}

vector<int> prod[200000];

vector<int> quotient(vector<int> A, vector<int> B){
	int n = A.size(), m = B.size();
	if(n < m) return vector<int>{0};
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	B.resize(n-m+1);
	A = conv(A, inversePolynomial(B));
	A.erase(A.begin() + n-m+1, A.end());
	reverse(A.begin(), A.end());
	return A;
}

vector<int> remainder(vector<int> A, vector<int> B){
	int n = A.size(), m = B.size();
	if(n >= m){
		vector<int> C = conv(quotient(A, B), B);
		A.resize(m-1);
		for(int i = 0; i < m-1; ++i)
			A[i] = modula(A[i] - C[i]);
	}
	return A;
}

int main(){
	//clock_t start = clock();
	int n;
	scanf("%d", &n);
	vector<int> a(n), inv_a(n), c(n);
	for(int & ai : a) scanf("%d", &ai);
	for(int i = 0; i < n; ++i) inv_a[i] = inverse(a[i], p);
	for(int & ci : c) scanf("%d", &ci);

	function<vector<int>(int, int)> sum_inv = [&](int l, int r){
		if(l == r)
			return vector<int>{1, p - a[l]};
		int m = (l + r) / 2;
		return conv(sum_inv(l, m), sum_inv(m + 1, r));
	};

	vector<int> P = sum_inv(0, n - 1);
	vector<int> dP(n);
	for(int i = 1; i <= n; ++i){
		dP[i-1] = (lli)i * P[i] % p;
	}

	vector<int> RHS = conv(P, c);
	RHS.resize(n);

	function<void(int, int, int)> pre = [&](int v, int l, int r){
		if(l == r) prod[v] = vector<int>{p - inv_a[l], 1};
		else{
			int y = (l + r) / 2;
			int z = v + (y - l + 1) * 2;
			pre(v + 1, l, y);
			pre(z, y + 1, r);
			prod[v] = conv(prod[v + 1], prod[z]);
		}
	};
	pre(0, 0, n - 1);

	function<int(const vector<int>&, int)> eval = [&](const vector<int> & poly, int x0){
		int ans = 0;
		for(int i = (int)poly.size()-1; i >= 0; --i){
			ans = modula((lli)ans * x0 % p + poly[i]);
		}
		return ans;
	};

	function<void(int, int, int, vector<int>, vector<int>&)> evaluate = [&](int v, int l, int r, vector<int> poly, vector<int> & res){
		poly = remainder(poly, prod[v]);
		if(poly.size() < 400){
			for(int i = l; i <= r; ++i)
				res[i] = eval(poly, inv_a[i]);
		}else{
			if(l == r)
				res[l] = poly[0];
			else{
				int y = (l + r) / 2;
				int z = v + (y - l + 1) * 2;
				evaluate(v + 1, l, y, poly, res);
				evaluate(z, y + 1, r, poly, res);
			}
		}
	};

	vector<int> RHS_eval(n), dP_eval(n);
	evaluate(0, 0, n - 1, RHS, RHS_eval);
	evaluate(0, 0, n - 1, dP, dP_eval);

	vector<int> b(n);
	for(int i = 0; i < n; ++i){
		b[i] = modula(-(lli)a[i] * RHS_eval[i] % p * inverse(dP_eval[i], p) % p);
	}

	for(int & bi : b) printf("%d ", bi);
	printf("\n");

	//printf("%0.3lf", (double)(clock() - start) / (double)CLOCKS_PER_SEC);

	return 0;
}