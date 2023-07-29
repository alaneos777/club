#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using poly = vector<int>;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli a, lli b, lli mod){
	lli ans = 1;
	if(b < 0) b += mod-1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

template<int p, int g>
void ntt(poly & X, int inv){
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
poly sq(poly A){
	int sz = 2*A.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size);
	ntt<p, g>(A, 1);
	for(int i = 0; i < size; i++){
		A[i] = (lli)A[i] * A[i] % p;
	}
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

const int a = 998244353, b = 985661441;
const lli a_b = powerMod(a, b-2, b);

template<int mod>
poly sq(const poly & A){
	poly P = sq<a, 3>(A);
	poly Q = sq<b, 3>(A);
	poly D(P.size());
	for(int i = 0; i < D.size(); ++i){
		int x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		int x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		D[i] = x1 % mod + (lli)a*x2 % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

template<int mod>
poly square(const poly& A){
	poly C = sq<mod>(A);
	for(int i = mod, j = 0; i < C.size(); ++i){
		C[j] += C[i];
		if(C[j] >= mod) C[j] -= mod;
		j++;
		if(j == mod) j = 0;
	}
	C.resize(min((int)C.size(), mod));
	return C;
}

template<int mod>
poly shift(const poly& A){
	poly B = A;
	B.resize(min((int)A.size()+1, mod));
	for(int i = 0, j = 1; i < A.size(); ++i){
		B[j] += A[i];
		if(B[j] >= mod) B[j] -= mod;
		j++;
		if(j == mod) j = 0;
	}
	return B;
}

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		lli q = a/b;
		auto[d, x, y] = extgcd(b, a - b*q);
		return {d, y, x - y*q};
	}
}

lli crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < a.size(); ++i){
		auto[d, s, t] = extgcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return -1;
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return x;
}

template<int mod>
lli S(lli n){
	poly R = {1};
	lli b = 1;
	for(lli v = n; v >>= 1; b <<= 1);
	do{
		R = square<mod>(R);
		if(n&b) R = shift<mod>(R);
	}while(b >>= 1);
	lli ans = 0;
	for(int k = 0; k < R.size(); ++k){
		(ans += powerMod(k, n, mod) * R[k]) %= mod;
	}
	return ans;
}

int main(){
	lli N = 1e18;
	lli ans = crt({S<571787>(N), S<704969>(N), S<912673>(N)}, {571787, 704969, 912673});
	cout << ans << "\n";
	return 0;
}