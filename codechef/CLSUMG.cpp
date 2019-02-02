#include <bits/stdc++.h>
using namespace std;
using ld = double;
typedef complex<ld> comp;
typedef long long int lli;
ld PI = acosl(-1.0l);

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void fft(vector<comp> & X, int inv){
	int n = X.size();
	int len, len2, i, j, k;
	for(i = 1, j = 0; i < n - 1; ++i){
		for(k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	ld ang;
	comp t, u, v;
	vector<comp> wlen_pw(n >> 1);
	wlen_pw[0] = 1;
	for(len = 2; len <= n; len <<= 1){
		ang = inv == -1 ? -2.0 * PI / len : 2.0 * PI / len;
		len2 = len >> 1;
		comp wlen(cos(ang), sin(ang));
		for(i = 1; i < len2; ++i)
			wlen_pw[i] = wlen_pw[i - 1] * wlen;
		for(i = 0; i < n; i += len)
			for(j = 0; j < len2; ++j){
				t = X[i + j + len2] * wlen_pw[j];
				X[i + j + len2] = X[i + j] - t;
				X[i + j] += t;
			}
	}
	if(inv == -1)
		for(i = 0; i < n; ++i)
			X[i] /= n;
}

vector<lli> conv(vector<lli> P, vector<lli> Q){
	vector<comp> A(P.size()), B(Q.size());
	for(int i = 0; i < P.size(); ++i)
		A[i] = P[i];
	for(int i = 0; i < Q.size(); ++i)
		B[i] = Q[i];
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	vector<comp> C(size);
	comp I(0, 1);
	for(int i = 0; i < A.size() || i < B.size(); ++i){
		if(i < A.size()) C[i] += A[i];
		if(i < B.size()) C[i] += I*B[i];
	}
	fft(C, 1);
	A.resize(size);
	for(int i = 0, j = 0; i < size; ++i){
		j = (size-1) & (size-i);
		A[i] = (conj(C[j]*C[j]) - C[i]*C[i]) * 0.25 * I;
	}
	fft(A, -1);
	A.resize(sz);
	vector<lli> R(A.size());
	for(int i = 0; i < R.size(); ++i)
		R[i] = round(real(A[i]));
	return R;
}

vector<lli> sieve(int n){
	vector<int> primes;
	vector<lli> isPrime(n+1, 1);
	isPrime[0] = isPrime[1] = 0;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i])
			primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = 0;
			if(i % p == 0) break;
		}
	}
	return isPrime;
}

int M = 1e6 + 10;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> isPrime = sieve(M);
	vector<lli> f = conv(isPrime, isPrime);
	f.resize(M+1);
	for(int i = 0; i <= M; ++i){
		if(isPrime[i] && i*2 <= M)
			f[i*2]++;
	}
	for(int i = 0; i <= M; ++i){
		assert(f[i]%2==0);
		f[i] /= 2;
	}
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		int N = *max_element(f.begin(), f.begin() + n) + 10;
		vector<lli> cnt(N+1);
		for(int i = 0; i < n; ++i)
			cnt[f[i]]++;
		vector<lli> g = conv(cnt, cnt);
		g.resize(N+1);
		for(int i = 0; i <= N; ++i){
			if(i*2 <= N)
				g[i*2] += cnt[i];
		}
		for(int i = 0; i <= N; ++i){
			assert(g[i]%2==0);
			g[i] /= 2;
		}
		cout << g[f[n]] << "\n";
	}
	return 0;
}