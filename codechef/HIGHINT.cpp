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

const int p = 786433;
const int root = 5;
const int root_1 = inverse(root, p);
const int root_pw = 1 << 18;

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, a, b;
	cin >> n >> k;
	vector<int> P(n+1), Q(n+1), B(n+1);
	for(int i = 1; i <= n; ++i){
		cin >> a >> b >> B[i];
		P[i] = (lli)a * inverse(b, p) % p;
		Q[i] = (1 - P[i]) % p;
		if(Q[i] < 0) Q[i] += p;
	}

	function<pair<vector<int>, vector<int>>(int, int)> sum = [&](int l, int r){
		if(l == r){
			return make_pair(vector<int>{int((lli)B[l] * P[l] % p)}, vector<int>{Q[l], P[l]});
		}
		int m = (l + r) / 2;
		vector<int> A, B, C, D;
		tie(A, B) = sum(l, m);
		tie(C, D) = sum(m+1, r);
		vector<int> num1 = convolution(A, D);
		vector<int> num2 = convolution(B, C);
		vector<int> den = convolution(B, D);
		for(int i = 0; i < num1.size(); ++i){
			num1[i] += num2[i];
			if(num1[i] >= p) num1[i] -= p;
		}
		return make_pair(num1, den);
	};
	vector<int> num, den;
	tie(num, den) = sum(1, n);
	num.resize(n+1);

	cout << num[k-1] << "\n";
	return 0;
}