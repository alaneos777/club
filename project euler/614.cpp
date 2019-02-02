#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

const lli mod = 1e9 + 7;

template<typename p, typename root, typename root_1, typename root_pw>
void ntt(vector<lli> & X, lli inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(int k = 1; k < n; k <<= 1){
		lli wk = (inv == -1) ? root_1::value : root::value;
		for(int i = k << 1; i < root_pw::value; i <<= 1)
			wk = wk * wk % p::value;
		for(int i = 0; i < n; i += k << 1){
			lli w = 1;
			for(int j = 0; j < k; ++j, w = w * wk % p::value){
				lli u = X[i + j], v = (lli)X[i + j + k] * w % p::value;
				X[i + j] = u + v < p::value ? u + v : u + v - p::value;
				X[i + j + k] = u - v < 0 ? u - v + p::value : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = inverse(n, p::value);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p::value;
	}
}

template<typename p, typename root, typename root_1, typename root_pw>
vector<lli> convolution(vector<lli> A, vector<lli> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<p, root, root_1, root_pw>(A, 1), ntt<p, root, root_1, root_pw>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = A[i] * B[i] % p::value;
	ntt<p, root, root_1, root_pw>(A, -1);
	A.resize(sz);
	return A;
}

const lli a = 167772161;  //17, 29606852
const lli b = 469762049;  //13, 144542169
const lli c = 1107296257; //309, 996208283
const lli a_b = inverse(a, b);
const lli a_c = inverse(a, c);
const lli b_c = inverse(b, c);
vector<lli> conv(const vector<lli> & A, const vector<lli> & B){
	vector<lli> P = convolution<integral_constant<lli, a>, integral_constant<lli, 17>, integral_constant<lli, 29606852>, integral_constant<lli, (1 << 25)>>(A, B);
	vector<lli> Q = convolution<integral_constant<lli, b>, integral_constant<lli, 13>, integral_constant<lli, 144542169>, integral_constant<lli, (1 << 25)>>(A, B);
	vector<lli> R = convolution<integral_constant<lli, c>, integral_constant<lli, 309>, integral_constant<lli, 996208283>, integral_constant<lli, (1 << 25)>>(A, B);
	vector<lli> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		lli x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		lli x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		lli x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 + a*(x2 + x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

vector<lli> inversePolynomial(const vector<lli> & A){
	vector<lli> R(1, inverse(A[0], mod));
	while(R.size() < A.size()){
		int c = 2 * R.size();
		R.resize(c);
		vector<lli> TR = R;
		vector<lli> TF(TR.size());
		for(int i = 0; i < c && i < A.size(); ++i)
			TF[i] = A[i];
		TR = conv(TR, TR);
		TR.resize(c);
		TR = conv(TR, TF);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - TR[i];
			if(R[i] < 0) R[i] += mod;
			if(R[i] >= mod) R[i] -= mod;
		}
	}
	R.resize(A.size());
	return R;
}

/*int main(){
	clock_t start = clock();
	int N = 1e7 + 1;
	vector<lli> B(N), B2P(N), B2N(N), B4(N);
	B[0] = 1;
	for(int i = 1; i*(3*i+1)/2 < N; ++i){
		B[i*(3*i+1)/2] = (i & 1) ? mod-1 : 1;
	}
	for(int i = 1; i*(3*i-1)/2 < N; ++i){
		B[i*(3*i-1)/2] = (i & 1) ? mod-1 : 1;
	}

	for(int i = 0; 2*i < N; ++i){
		B2P[2*i] = B[i];
		B2N[2*i] = (i & 1) ? (mod-B[i])%mod : B[i];
	}
	for(int i = 0; 4*i < N; ++i){
		B4[4*i] = B[i];
	}

	vector<lli> num = conv(B2P, B4);
	vector<lli> den = conv(B, B2N);
	num.resize(N);
	den.resize(N);
	vector<lli> ans = conv(num, inversePolynomial(den));
	ans.resize(N);

	lli sum = 0;
	for(int i = 1; i < N; ++i){
		sum += ans[i];
		if(sum >= mod) sum -= mod;
		//cout << i << " -> " << ans[i] << "\n";
	}
	cout << sum << "\n";
	cout << fixed << setprecision(3) << (double)(clock() - start)/(double)CLOCKS_PER_SEC << "\n";
	return 0;
}*/

int main(){
	clock_t start = clock();
	int N = 1e7 + 1;
	vector<lli> num(N), den(N);
	den[0] = 1;
	for(int i = 1; 2*i*i-i < N; ++i){
		den[2*i*i-i] = (i & 1) ? mod-1 : 1;
	}
	for(int i = 1; 2*i*i+i < N; ++i){
		den[2*i*i+i] = (i & 1) ? mod-1 : 1;
	}
	for(int i = 0; 2*i < N; ++i){
		num[2*i] = den[i];
	}

	vector<lli> ans = conv(num, inversePolynomial(den));
	ans.resize(N);

	lli sum = 0;
	for(int i = 1; i < N; ++i){
		sum += ans[i];
		if(sum >= mod) sum -= mod;
		//cout << i << " -> " << ans[i] << "\n";
	}
	cout << sum << "\n";
	cout << fixed << setprecision(3) << (double)(clock() - start)/(double)CLOCKS_PER_SEC << "\n";
	return 0;
}