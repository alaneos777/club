#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

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

vector<int> conv(const vector<int>& a, const vector<int>& b){
	vector<int> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += (lli)a[i]*b[j] % mod;
			if(c[i+j] >= mod) c[i+j] -= mod;
		}
	}
	return c;
}

vector<int> inversePolynomial(const vector<int> & A){
	vector<int> R(1, powerMod(A[0], mod - 2, mod));
	while(R.size() < A.size()){
		size_t c = 2 * R.size();
		R.resize(c);
		vector<int> R2 = R;
		vector<int> a(min(c, A.size()));
		for(int i = 0; i < a.size(); ++i)
			a[i] = A[i];
		R2 = conv(R2, R2);
		R2.resize(c);
		R2 = conv(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += mod;
			if(R[i] >= mod) R[i] -= mod;
		}
	}
	R.resize(A.size());
	return R;
}

vector<int> derivative(vector<int> A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = (lli)A[i] * i % mod;
	if(!A.empty()) A.erase(A.begin());
	return A;
}

vector<int> integral(vector<int> A){
	for(int i = 0; i < A.size(); ++i)
		A[i] = (lli)A[i] * (powerMod(i+1, mod-2, mod)) % mod;
	A.insert(A.begin(), 0);
	return A;
}

vector<int> logarithm(vector<int> A){
	assert(A[0] == 1);
	int n = A.size();
	A = conv(derivative(A), inversePolynomial(A));
	A.resize(n);
	A = integral(A);
	A.resize(n);
	return A;
}

vector<int> exponential(const vector<int> & A){
	assert(A[0] == 0);
	vector<int> E(1, 1);
	while(E.size() < A.size()){
		size_t c = 2*E.size();
		E.resize(c);
		vector<int> S = logarithm(E);
		for(int i = 0; i < c && i < A.size(); ++i){
			S[i] = A[i] - S[i];
			if(S[i] < 0) S[i] += mod;
		}
		S[0] = 1;
		E = conv(E, S);
		E.resize(c);
	}
	E.resize(A.size());
	return E;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> inv(k+2, 1), fact(k+2, 1), invfact(k+2, 1);
	for(lli i = 2; i <= k+1; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	vector<int> num(k+2), den(k+2);
	for(int i = 1; i <= k+1; ++i){
		num[i] = powerMod(n, i, mod) * invfact[i] % mod;
		den[i] = invfact[i];
	}
	num.erase(num.begin());
	den.erase(den.begin());
	vector<int> P = conv(num, inversePolynomial(den));
	P.resize(k+1);
	for(int i = 1; i <= k; ++i){
		P[i] = (lli)P[i] * fact[i] % mod;
	}
	vector<int> ln(k+1);
	for(int j = 1; j <= k; ++j){
		if(j & 1){
			ln[j] = lli(1 + P[j]-1) * inv[j] % mod;
		}else{
			ln[j] = lli(1 + 1-P[j]) * inv[j] % mod;
			if(ln[j] < 0) ln[j] += mod;
		}
	}
	vector<int> res = exponential(ln);
	for(int i = 1; i <= k; ++i){
		cout << res[i] << " ";
	}
	cout << "\n";
	return 0;
}