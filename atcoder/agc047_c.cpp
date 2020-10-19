#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

__int128_t powerMod(__int128_t b, __int128_t e, __int128_t m){
	__int128_t ans = 1;
	e %= m-1;
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
	vector<__int128_t> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		__int128_t wk = powerMod(g, inv * (p - 1) / (k<<1), p);
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
		__int128_t nrev = powerMod(n, p - 2, p);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p;
	}
}

template<lli p, lli g>
vector<lli> sq(vector<lli> A){
	int sz = A.size();
	int size = nearestPowerOfTwo(2*A.size() - 1);
	A.resize(size);
	ntt<p, g>(A, 1);
	for(int i = 0; i < size; i++)
		A[i] = (__int128_t)A[i] * A[i] % p;
	ntt<p, g>(A, -1);
	for(int i = sz; i < size; ++i){
		A[i % sz] += A[i];
	}
	A.resize(sz);
	return A;
}

const int P = 2e5 + 3;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> LOG(P);
	vector<int> g_pow(P-1, 1);
	for(int i = 1; i < P-1; ++i){
		g_pow[i] = (lli)g_pow[i-1] * 5 % P;
		assert(g_pow[i] != 1);
		LOG[g_pow[i]] = i;
	}
	int n;
	cin >> n;
	vector<lli> poly(P-1);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		if(ai){
			poly[LOG[ai]]++;
		}
	}
	auto freq = sq<17169973579350017ll, 3>(poly);
	for(int i = 0; i < P-1; ++i){
		freq[2*i % (P-1)] -= poly[i];
	}
	for(int i = 0; i < P-1; ++i){
		assert(freq[i] % 2 == 0);
		freq[i] /= 2;
	}
	lli ans = 0;
	for(int i = 0; i < P-1; ++i){
		ans += g_pow[i] * freq[i];
	}
	cout << ans << "\n";
	return 0;
}