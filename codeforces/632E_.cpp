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

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, ai, maxi = 0;
	cin >> n >> k;
	vector<int> P;
	for(int i = 0; i < n; ++i){
		cin >> ai;
		if(ai >= P.size()) P.resize(ai + 1);
		P[ai] = 1;
		maxi = max(maxi, ai);
	}
	int sz = maxi*k + 1;
	int N = nearestPowerOfTwo(sz);
	P.resize(N);
	ntt(P, 1);
	for(int i = 0; i < N; ++i){
		P[i] = powerMod(P[i], k);
	}
	ntt(P, -1);
	for(int i = 0; i < sz; ++i){
		if(P[i]) cout << i << " ";
	}
	return 0;
}