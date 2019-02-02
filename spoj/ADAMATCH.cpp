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

const int p = 167772161;
const int root = 4;
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

void convolution(vector<int> & A, vector<int> & B){
	int degree = A.size() + B.size() - 2;
	int size = nearestPowerOfTwo(degree + 1);
	A.resize(size);
	B.resize(size);
	ntt(A, 1);
	ntt(B, 1);
	for(int i = 0; i < size; i++){
		A[i] = (lli)A[i] * B[i] % p;
	}
	ntt(A, -1);
	A.resize(degree + 1);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string S, R;
	cin >> S >> R;
	int s = S.size(), r = R.size();
	reverse(R.begin(), R.end());
	vector<char> alpha = {'A', 'C', 'G', 'T'};
	vector<int> ans(s);
	for(char c : alpha){
		vector<int> a(s), b(r);
		for(int i = 0; i < s; ++i){
			if(S[i] == c) a[i] = 1;
		}
		for(int i = 0; i < r; ++i){
			if(R[i] == c) b[i] = 1;
		}
		convolution(a, b);
		for(int i = r - 1; i < s; ++i){
			ans[i] += a[i];
		}
	}
	int resp = 1<<30;
	for(int i = r - 1; i < s; ++i){
		resp = min(resp, r - ans[i]);
	}
	cout << resp << "\n";
	return 0;
}