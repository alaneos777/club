#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	e %= m-1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

template<int p, int g>
void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, inv * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % p;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = powerMod(n, p - 2, p);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p;
	}
}

template<int p, int g>
vector<int> convolution(vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<p, g>(A, 1), ntt<p, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

const int a = 998244353, b = 985661441;
const lli a_b = powerMod(a, b-2, b);
vector<lli> conv(const vector<int> & A, const vector<int> & B){
	vector<int> P = convolution<a, 3>(A, B);
	vector<int> Q = convolution<b, 3>(A, B);
	vector<lli> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		lli x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		lli x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		D[i] = x1 + a*x2;
	}
	return D;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, x;
	cin >> n >> x;
	vector<int> s(n+1);
	for(int i = 1; i <= n; ++i){
		int ai;
		cin >> ai;
		s[i] = (ai < x);
	}
	partial_sum(s.begin(), s.end(), s.begin());
	lli ans0 = 0;
	lli len = 0;
	int prev = -1;
	for(int i = 0; i <= n; ++i){
		if(s[i] == prev){
			len++;
		}else{
			ans0 += len*(len-1)/2;
			len = 1;
		}
		prev = s[i];
	}
	ans0 += len*(len-1)/2;
	int M = *max_element(s.begin(), s.end());
	vector<int> P(M+1), Q(M+1);
	for(int si : s){
		P[si]++;
	}
	Q = P;
	reverse(Q.begin(), Q.end());
	vector<lli> R = conv(P, Q);
	R.resize(M+n+1);
	cout << ans0;
	for(int i = 1; i <= n; ++i){
		cout << " " << R[M+i];
	}
	cout << "\n";
	return 0;
}