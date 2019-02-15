#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const int p = 104857601;
const int root = 21;
const int root_1 = inverse(root, p);
const int root_pw = 1 << 22;

void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(int k = 1; k < n; k <<= 1){
		int wk = (inv == -1) ? root_1 : root;
		for(int i = k << 1; i < root_pw; i <<= 1)
			wk = (lli)wk * wk % p;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0, w = 1; j < k; ++j, w = (lli)w * wk % p){
				int u = X[i + j], v = (lli)X[i + j + k] * w % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
		}
	}
	if(inv == -1){
		int nrev = inverse(n, p);
		for(int i = 0; i < n; ++i)
			X[i] = (lli)X[i] * nrev % p;
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
			R[i] = R[i] + R[i] - TR[i];
			if(R[i] < 0) R[i] += p;
			if(R[i] >= p) R[i] -= p;
		}
	}
	R.resize(A.size());
	return R;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int k; lli n;
	cin >> k >> n;
	--n;
	vector<int> init(k), poly(k);
	for(int & ai : init) cin >> ai;
	for(int & ai : poly) cin >> ai;

	for(int i = 0; i < k; ++i) poly[i] = (p - poly[i]) % p;
	poly.insert(poly.begin(), 1);
	vector<int> inv = inversePolynomial(poly);
	reverse(poly.begin(), poly.end());

	int sz = nearestPowerOfTwo(2*k);
	inv.resize(sz);
	poly.resize(sz);
	ntt(inv, 1);
	ntt(poly, 1);

	vector<int> ans(k);
	ans[0] = 1;
	lli pw = 1;
	for(lli v = n; v >>= 1; pw <<= 1);
	do{
		int d = (n & pw) != 0;
		ans.resize(sz);
		ntt(ans, 1);
		for(int i = 0; i < sz; ++i){
			ans[i] = (lli)ans[i] * ans[i] % p;
		}
		ntt(ans, -1);
		ans.resize(2*k - 1);
		if(d) ans.insert(ans.begin(), 0);
		else ans.push_back(0);

		vector<int> Q(sz);
		copy(ans.rbegin(), ans.rbegin() + k, Q.begin());
		ntt(Q, 1);
		for(int i = 0; i < sz; ++i){
			Q[i] = (lli)Q[i] * inv[i] % p;
		}
		ntt(Q, -1);
		Q.resize(k);
		reverse(Q.begin(), Q.end());

		Q.resize(sz);
		ntt(Q, 1);
		for(int i = 0; i < sz; ++i){
			Q[i] = (lli)Q[i] * poly[i] % p;
		}
		ntt(Q, -1);

		ans.resize(k);
		for(int i = 0; i < k; ++i){
			ans[i] -= Q[i];
			if(ans[i] < 0) ans[i] += p;
		}
	}while(pw >>= 1);

	int nVal = 0;
	for(int i = 0; i < k; ++i){
		nVal += (lli)ans[i] * init[i] % p;
		if(nVal >= p) nVal -= p;
	}

	cout << nVal << "\n";
	return 0;
}