#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using poly = vector<int>;

template<lli mod>
lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

template<int mod, int g>
void ntt(poly& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n-1; ++i){
		for(int k = n>>1; (j^=k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz <<= 1){
		lli w_1 = powerMod<mod>(g, (mod-1)/sz);
		if(inv == -1) w_1 = powerMod<mod>(w_1, mod-2);
		vector<lli> w(sz/2, 1);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w_1 * w[j-1] % mod;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = w[j] * a[start + sz/2 + j] % mod;
				a[start + j] = (u+v >= mod ? u+v-mod : u+v);
				a[start + sz/2 + j] = (u-v < 0 ? u-v+mod : u-v);
			}
		}
	}
	if(inv == -1){
		lli n_rev = powerMod<mod>(n, mod-2);
		for(int& ai : a){
			ai = ai * n_rev % mod;
		}
	}
}

template<int mod, int g>
poly convolution(poly a, poly b){
	int sz = a.size() + b.size() - 1;
	int SZ = nearestPowerOfTwo(sz);
	a.resize(SZ), b.resize(SZ);
	ntt<mod, g>(a, 1), ntt<mod, g>(b, 1);
	poly c(SZ);
	for(int i = 0; i < SZ; ++i){
		c[i] = (lli)a[i] * b[i] % mod;
	}
	ntt<mod, g>(c, -1);
	c.resize(sz);
	return c;
}

const int p = 998244353, g = 3;

poly inversePolynomial(const poly & A){
	poly R(1, powerMod<p>(A[0], p - 2));
	//R(x) = 2R(x)-A(x)R(x)^2
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		poly R2 = R;
		poly a(min(c, A.size()));
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

//returns Q(x), where A(x)=B(x)Q(x)+R(x)
poly quotient(poly A, poly B){
	int n = A.size(), m = B.size();
	if(n < m) return poly{0};
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(n-m+1), B.resize(n-m+1);
	A = convolution<p, g>(A, inversePolynomial(B));
	A.resize(n-m+1);
	reverse(A.begin(), A.end());
	return A;
}

//returns R(x), where A(x)=B(x)Q(x)+R(x)
poly remainder(poly A, const poly & B){
	int n = A.size(), m = B.size();
	if(n >= m){
		poly C = convolution<p, g>(quotient(A, B), B);
		A.resize(m-1);
		for(int i = 0; i < m-1; ++i){
			A[i] -= C[i];
			if(A[i] < 0) A[i] += p;
		}
	}
	return A;
}

poly multiEvaluate(const poly & P, const poly & points){
	int n = points.size();
	vector<poly> t(n<<1), r(n<<1), e(n<<1);
	vector<bool> calc(n<<1);
	poly ans(n);
	for(int i = 0; i < n; ++i){
		t[n+i] = {(p - points[i]) % p, 1};
		e[n+i].push_back(i);
	}
	for(int i = n-1; i > 0; --i){
		t[i] = convolution<p, g>(t[i<<1], t[i<<1|1]);
		e[i] = e[i<<1];
		e[i].insert(e[i].end(), e[i<<1|1].begin(), e[i<<1|1].end());
	}
	auto naive = [&](const poly& P, int x){
		int y = 0;
		for(int i = (int)P.size()-1; i >= 0; --i){
			y = ((lli)y*x + P[i]) % p;
		}
		return y;
	};
	r[1] = remainder(P, t[1]);
	for(int i = 1; i < n; ++i){
		if(calc[i]){
			calc[i<<1] = calc[i<<1|1] = true;
		}else if(e[i].size() < 400){
			for(int pos : e[i]){
				r[n+pos] = {naive(r[i], points[pos])};
			}
			calc[i<<1] = calc[i<<1|1] = true;
		}else{
			r[i<<1] = remainder(r[i], t[i<<1]);
			r[i<<1|1] = remainder(r[i], t[i<<1|1]);
		}
	}
	for(int i = 0; i < n; ++i){
		ans[i] = r[n+i][0];
	}
	return ans;
}

poly derivative(poly A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = (lli)A[i] * i % p;
	if(!A.empty()) A.erase(A.begin());
	return A;
}

poly interpolate(const poly& X, const poly& Y){
	int n = X.size();
	vector<poly> t(n<<1), r(n<<1);
	poly ans(n);
	for(int i = 0; i < n; ++i){
		t[n+i] = {(p - X[i]) % p, 1};
	}
	for(int i = n-1; i > 0; --i){
		t[i] = convolution<p, g>(t[i<<1], t[i<<1|1]);
	}
	poly Q = multiEvaluate(derivative(t[1]), X);
	for(int i = 0; i < n; ++i){
		r[n+i] = {Y[i] * powerMod<p>(Q[i], p-2) % p};
	}
	for(int i = n-1; i > 0; --i){
		r[i] = convolution<p, g>(r[i<<1], t[i<<1|1]);
		poly rhs = convolution<p, g>(r[i<<1|1], t[i<<1]);
		r[i].resize(max(r[i].size(), rhs.size()));
		for(int j = 0; j < rhs.size(); ++j){
			r[i][j] += rhs[j];
			if(r[i][j] >= p) r[i][j] -= p;
		}
	}
	return r[1];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	poly x(n), y(n);
	for(int& xi : x){
		cin >> xi;
	}
	for(int& yi : y){
		cin >> yi;
	}
	poly ans = interpolate(x, y);
	for(int i = 0; i < ans.size(); ++i){
		cout << ans[i] << " ";
	}
	cout << "\n";
	return 0;
}