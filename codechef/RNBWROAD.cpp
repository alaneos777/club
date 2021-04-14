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

vector<int> inversePolynomial(const vector<int> & A){
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
	return R;
}

vector<int> derivative(vector<int> A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = (lli)A[i] * i % p;
	if(!A.empty()) A.erase(A.begin());
	return A;
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

vector<int> multiEvaluate(const vector<int> & P, const vector<int> & points){
	int n = points.size();
	vector<vector<int>> prod(2*n - 1);
	function<void(int, int, int)> pre = [&](int v, int l, int r){
		if(l == r) prod[v] = vector<int>{(p - points[l]) % p, 1};
		else{
			int y = (l + r) / 2;
			int z = v + (y - l + 1) * 2;
			pre(v + 1, l, y);
			pre(z, y + 1, r);
			prod[v] = convolution<p, g>(prod[v + 1], prod[z]);
		}
	};
	pre(0, 0, n - 1);

	function<int(const vector<int>&, int)> eval = [&](const vector<int> & poly, int x0){
		int ans = 0;
		for(int i = (int)poly.size()-1; i >= 0; --i){
			ans = (lli)ans * x0 % p + poly[i];
			if(ans >= p) ans -= p;
		}
		return ans;
	};

	vector<int> res(n);
	function<void(int, int, int, vector<int>)> evaluate = [&](int v, int l, int r, vector<int> poly){
		poly = remainder(poly, prod[v]);
		if(poly.size() < 400){
			for(int i = l; i <= r; ++i)
				res[i] = eval(poly, points[i]);
		}else{
			if(l == r)
				res[l] = poly[0];
			else{
				int y = (l + r) / 2;
				int z = v + (y - l + 1) * 2;
				evaluate(v + 1, l, y, poly);
				evaluate(z, y + 1, r, poly);
			}
		}
	};
	evaluate(0, 0, n - 1, P);
	return res;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli m; int n, q;
	cin >> m >> n >> q;
	vector<int> a(n);
	lli fact = 1;
	for(int& ai : a){
		cin >> ai;
		fact = fact * ai % p;
	}
	function<vector<int>(int, int)> prod = [&](int l, int r){
		if(l == r) return vector<int>{1, p - a[l]};
		int m = (l+r)/2;
		return convolution<p,g>(prod(l, m), prod(m+1, r));
	};
	vector<int> P = prod(0, n-1);
	if(m <= 1e5){
		P.resize(1e5);
		vector<int> init = inversePolynomial(P);
		for(int& ii : init){
			ii = ii * fact % p;
		}
		while(q--){
			int k;
			cin >> k;
			cout << init[k-1] << "\n";
		}
	}else{
		vector<int> Pp = derivative(P);
		assert(Pp.size() == n);
		vector<int> c(n);
		for(int i = 0; i < n; ++i){
			c[i] = powerMod(a[i], -1, p);
		}
		c = multiEvaluate(Pp, c);
		for(int i = 0; i < n; ++i){
			c[i] = powerMod(c[i], -1, p) * fact % p * (p - a[i]) % p;
		}

		while(q--){
			lli k;
			cin >> k;
			lli ans = 0;
			for(int i = 0; i < n; ++i){
				(ans += c[i]*powerMod(a[i], k-1, p)) %= p;
			}
			cout << ans << "\n";
		}
	}
	return 0;
}