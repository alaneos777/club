#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli inverse(lli a, lli mod){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += mod;
	return s0;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

template<lli p, lli g>
void ntt(vector<lli> & X, int inv){
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
				lli u = X[i + j], v = X[i + j + k] * wp[j] % p;
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

template<lli p, lli g>
vector<lli> convolution(vector<lli> A, vector<lli> B, bool same){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size);
	ntt<p, g>(A, 1);
	if(!same){
		B.resize(size);
		ntt<p, g>(B, 1);
	}
	for(int i = 0; i < size; i++){
		A[i] = (lli)A[i] * (same ? A[i] : B[i]) % p;
	}
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

const lli a = 33706903339009ll, b = 33913061769217ll, c = 34187939676161ll;
const lli a_b = powerMod(a, b-2, b), a_c = powerMod(a, c-2, c), b_c = powerMod(b, c-2, c);
vector<lli> conv(const vector<lli> & A, const vector<lli> & B, bool same){
	vector<lli> P = convolution<a, 7>(A, B, same);
	vector<lli> Q = convolution<b, 5>(A, B, same);
	vector<lli> R = convolution<c, 3>(A, B, same);
	vector<lli> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		lli x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		lli x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		lli x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 + a*(x2 + x3*b);
	}
	return D;
}

const lli rd = 1e16;

auto mult(const vector<lli> & a, const vector<lli> & b, bool same){
	auto c = conv(a, b, same);
	lli carry = 0;
	for(int i = 0; i < c.size(); ++i){
		c[i] += carry;
		carry = c[i] / rd;
		c[i] %= rd;
	}
	while(carry){
		c.push_back(carry % rd);
		carry /= rd;
	}
	return c;
}

vector<lli> operator*(vector<lli> a, lli k){
	for(lli & ai : a){
		ai *= k;
	}
	lli carry = 0;
	for(int i = 0; i < a.size(); ++i){
		a[i] += carry;
		carry = a[i] / rd;
		a[i] %= rd;
	}
	while(carry){
		a.push_back(carry % rd);
		carry /= rd;
	}
	return a;
}

auto power(int b){
	int p = 1; for(int v = b; v >>= 1; p <<= 1);
	vector<lli> ans = {1};
	do{
		ans = mult(ans, ans, true);
		if(b & p) ans = ans * 3;
	}while(p >>= 1);
	return ans;
}

bool operator<(const vector<lli> & a, const vector<lli> & b){
	if(a.size() < b.size()) return true;
	if(a.size() > b.size()) return false;
	for(int i = 0; i < a.size(); ++i){
		if(a[a.size()-1-i] < b[b.size()-1-i]) return true;
		if(a[a.size()-1-i] > b[b.size()-1-i]) return false;
	}
	return a.back() < b.back();
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string str;
	cin >> str;
	reverse(str.begin(), str.end());
	if(str.size() == 1 && str[0] <= '4'){
		cout << str << "\n";
		return 0;
	}
	vector<lli> n;
	lli acum = 0, ten = 1;
	for(int i = 0; i < str.size(); ++i){
		acum += ten * (str[i] - '0');
		ten *= 10;
		if(i % 16 == 15){
			n.push_back(acum);
			acum = 0;
			ten = 1;
		}
	}
	if(acum){
		n.push_back(acum);
	}
	int m = (log10l(str.back()-'0') + (str.size()-1)) / log10l(3) - log10l(4)/log10l(3);
	m = max(0, m-1);
	vector<lli> three = power(m);
	auto cp = three;
	int m1 = m, m2 = m, m3 = m;
	while(three < n){
		three = three * 3;
		m1++;
	}
	three = cp * 2;
	while(three < n){
		three = three * 3;
		m2++;
	}
	three = cp * 4;
	while(three < n){
		three = three * 3;
		m3++;
	}
	m1 = 3*m1, m2 = 3*m2 + 2, m3 = 3*m3 + 4;
	cout << min({m1, m2, m3}) << "\n";
	return 0;
}