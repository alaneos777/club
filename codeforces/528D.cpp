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

const int p = 1 + (119<<23);
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
	int S, T, k;
	string s, t;
	cin >> S >> T >> k;
	cin >> s >> t;
	vector<bool> ans(S-T+1, true);
	for(char c : {'A', 'T', 'G', 'C'}){
		vector<int> A(S), on(S), off(S), B(T);
		for(int i = 0; i < S; ++i){
			if(s[i] == c){
				on[max(0, i-k)]++;
				off[min(S-1, i+k)]++;
			}
		}
		int turn = 0;
		for(int i = 0; i < S; ++i){
			turn += on[i];
			if(turn > 0) A[i] = 1;
			turn -= off[i];
		}
		int freq = 0;
		for(int i = 0; i < T; ++i){
			B[i] = (t[i] == c);
			freq += (t[i] == c);
		}
		reverse(B.begin(), B.end());
		vector<int> res = convolution(A, B);
		for(int i = 0; i <= S-T; ++i){
			ans[i] = ans[i] & (res[i + T - 1] == freq);
		}
	}
	int cnt = 0;
	for(int i = 0; i <= S-T; ++i){
		cnt += ans[i];
	}
	cout << cnt << "\n";
	return 0;
}