#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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
	if(A == B) ntt<p, g>(A, 1), B = A;
	else ntt<p, g>(A, 1), ntt<p, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

const int p = 998244353, g = 3;

map<vector<int>, vector<int>> mem;
vector<int> inversePolynomial(const vector<int> & A){
	if(mem.count(A)) return mem[A];
	vector<int> R(1, powerMod(A[0], p - 2, p));
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<int> R2 = R;
		vector<int> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = convolution<p, g>(R2, R2);
		R2.resize(c);
		R2 = convolution<p, g>(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += p;
			if(R[i] >= p) R[i] -= p;
		}
	}
	R.resize(A.size());
	return mem[A] = R;
}

vector<int> quotient(vector<int> A, vector<int> B){
	int n = A.size(), m = B.size();
	if(n < m) return vector<int>{0};
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(n-m+1), B.resize(n-m+1);
	A = convolution<p, g>(A, inversePolynomial(B));
	A.resize(n-m+1);
	reverse(A.begin(), A.end());
	return A;
}

vector<int> remainder(vector<int> A, const vector<int> & B){
	int n = A.size(), m = B.size();
	if(n >= m){
		vector<int> C = convolution<p, g>(quotient(A, B), B);
		A.resize(m-1);
		for(int i = 0; i < m-1; ++i){
			A[i] -= C[i];
			if(A[i] < 0) A[i] += p;
		}
	}
	return A;
}

lli rec(const vector<int> & P, const vector<int> & init, lli n){
	int deg = (int)P.size()-1;
	vector<int> ans(deg);
	ans[0] = 1;
	lli pot = 1;
	for(lli v = n; v >>= 1; pot <<= 1);
	do{
		int d = (n & pot) != 0;
		ans = convolution<p,g>(ans, ans);
		if(d == 1) ans.insert(ans.begin(), 0);
		ans = remainder(ans, P);
	}while(pot >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += (lli)ans[i] * init[i]) %= p;
	return nValue;
}

const lli M = 60000;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % p;
		inv[i] = p - (p / i) * inv[p % i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	auto ncr = [&](int n, int k){
		if(k < 0 || k > n) return 0ll;
		return (lli)fact[n] * invfact[k] % p * invfact[n-k] % p;
	};
	int n; lli m;
	cin >> n >> m;
	vector<int> freq(M+1);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		freq[ai]++;
	}
	vector<vector<int>> polys;
	for(int ai = 1; ai <= M; ++ai){
		if(freq[ai]){ // (1-x^a[i])^freq[a[i]]
			vector<int> P(ai*freq[ai]+1);
			for(int k = 0; k <= freq[ai]; ++k){
				P[ai*k] = ncr(freq[ai], k);
				if((k & 1) == 1 && P[ai*k] > 0) P[ai*k] = p - P[ai*k];
			}
			polys.emplace_back(P);
		}
	}
	function<vector<int>(int, int)> prod = [&](int l, int r){
		if(l == r) return polys[l];
		int m = (l+r)/2;
		return convolution<p,g>(prod(l, m), prod(m+1, r));
	};
	vector<int> P = prod(0, polys.size()-1);
	vector<int> init = inversePolynomial(P);

	reverse(P.begin(), P.end());
	/*P.pop_back();
	for(int& pi : P){
		pi = (p - pi) % p;
	}*/

	cout << rec(P, init, m) << "\n";
	return 0;
}