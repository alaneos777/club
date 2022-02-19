#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using poly = vector<int>;
const int p = 998244353, g = 3;

int near(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
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

void ntt(poly& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n-1; ++i){
		for(int k = n>>1; (j^=k) < k; k>>=1);
		if(i < j) swap(a[i], a[j]);
	}
	vector<lli> w(n>>1, 1);
	for(int sz = 2; sz <= n; sz<<=1){
		lli w_sz = powerMod(g, (p-1)/sz);
		if(inv == -1) w_sz = powerMod(w_sz, p-2);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w[j-1] * w_sz % p;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = a[start + j + sz/2] * w[j] % p;
				a[start + j] = u+v >= p ? u+v-p : u+v;
				a[start + j + sz/2]= u-v < 0 ? u-v+p : u-v;
			}
		}
	}
	if(inv == -1){
		lli ninv = powerMod(n, p-2);
		for(int& ai : a){
			ai = ai * ninv % p;
		}
	}
}

poly convolution(poly A, poly B){
	int sz = A.size() + B.size() - 1;
	int size = near(sz);
	A.resize(size), B.resize(size);
	ntt(A, 1), ntt(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt(A, -1);
	A.resize(sz);
	return A;
}

poly inversePolynomial(const poly & A){
	poly R(1, powerMod(A[0], p - 2));
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		poly R2 = R;
		poly a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = convolution(R2, R2);
		R2.resize(c);
		R2 = convolution(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += p;
			if(R[i] >= p) R[i] -= p;
		}
	}
	R.resize(A.size());
	return R;
}

poly quotient(poly A, poly B){
	int n = A.size(), m = B.size();
	if(n < m) return poly{};
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	A.resize(n-m+1), B.resize(n-m+1);
	A = convolution(A, inversePolynomial(B));
	A.resize(n-m+1);
	reverse(A.begin(), A.end());
	return A;
}

poly remainder(poly A, const poly & B){
	int n = A.size(), m = B.size();
	if(n >= m){
		poly C = convolution(quotient(A, B), B);
		A.resize(m-1);
		for(int i = 0; i < m-1; ++i){
			A[i] -= C[i];
			if(A[i] < 0) A[i] += p;
		}
	}
	return A;
}

vector<int> multiEvaluate(const poly & P, const vector<int> & points){
	int n = points.size();
	vector<poly> t(n<<1), r(n<<1); vector<vector<int>> e(n<<1);
	vector<bool> calc(n<<1);
	vector<int> ans(n);
	for(int i = 0; i < n; ++i){
		t[n+i] = {(p - points[i]) % p, 1};
		e[n+i].push_back(i);
	}
	for(int i = n-1; i > 0; --i){
		t[i] = convolution(t[i<<1], t[i<<1|1]);
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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, k;
	cin >> m >> k;
	vector<int> fact(k+2, 1), inv(k+2, 1), invfact(k+2, 1);
	for(lli i = 2; i <= k+1; ++i){
		fact[i] = i * fact[i-1] % p;
		inv[i] = p - (p / i) * inv[p % i] % p;
		invfact[i] = (lli)inv[i] * invfact[i-1] % p;
	}
	vector<int> B(k+1);
	for(int i = 0; i <= k; ++i){
		B[i] = invfact[i+1];
		if(i&1) B[i] = p - B[i];
	}
	B = inversePolynomial(B);
	poly P(k+2);
	for(int i = 0; i <= k; ++i){
		P[k+1-i] = (lli)B[i] * fact[k+1] % p * invfact[k+1-i] % p * inv[k+1] % p;
	}
	vector<int> points(m);
	for(int i = 0; i < m; ++i){
		lli pi;
		cin >> pi;
		points[i] = pi % p;
	}
	auto ans = multiEvaluate(P, points);
	for(int ai : ans){
		cout << ai << " ";
	}
	cout << "\n";
	return 0;
}