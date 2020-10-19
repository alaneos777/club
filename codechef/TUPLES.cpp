#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

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
	ntt<p, g>(A, 1), ntt<p, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

const int mod = 1e9 + 7;

const int a = 998244353, b = 985661441;
const lli a_b = powerMod(a, b-2, b);
vector<int> conv(const vector<int> & A, const vector<int> & B){
	vector<int> P = convolution<a, 3>(A, B);
	vector<int> Q = convolution<b, 3>(A, B);
	vector<int> D(P.size());
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

const int m = 359999;
const int g = 7;
const int m1 = 599, m2 = 601;
const int order = (m1-1)*(m2-1)/2;

vector<int> sieve(int n){
	vector<int> mu(n+1, -1);
	mu[0] = 0, mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(mu[i]){
			for(int j = 2*i; j <= n; j += i){
				mu[j] -= mu[i];
			}
		}
	}
	return mu;
}

const auto mu = sieve(m-1);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> A(m, -1), B(m, -1), C(m, -1), D(m, -1), g_pow(order, 1);
	for(int i = 0; i < order; ++i){
		A[g_pow[i]] = i;
		B[g_pow[i] * 17 % m] = i;
		if(i < m2){
			C[g_pow[i] * m1 % m] = i;
		}
		if(i < m1){
			D[g_pow[i] * m2 % m] = i;
		}
		if(i+1 < order) g_pow[i+1] = (lli)g_pow[i] * g % m;
	}
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> p(order), q(order), r(m2), s(m1);
		int z_cnt = 0, nz_cnt = n, r_cnt = 0, s_cnt = 0;
		while(n--){
			int ai;
			cin >> ai;
			ai %= m;
			if(ai == 0) z_cnt++, nz_cnt--;
			else if(A[ai] != -1) p[A[ai]]++;
			else if(B[ai] != -1) q[B[ai]]++;
			else if(C[ai] != -1) r[C[ai]]++, r_cnt++;
			else if(D[ai] != -1) s[D[ai]]++, s_cnt++;
			else assert(0);
		}

		vector<int> freq(m);
		vector<int> p2 = conv(p, p);
		for(int i = 0; i < p2.size(); ++i){
			(freq[g_pow[i % order]] += p2[i]) %= mod;
		}
		vector<int> q2 = conv(q, q);
		for(int i = 0; i < q2.size(); ++i){
			(freq[g_pow[(i + 21370) % order]] += q2[i]) %= mod;
		}
		vector<int> r2 = conv(r, r);
		for(int i = 0; i < r2.size(); ++i){
			(freq[g_pow[(i + 132) % order] * m1 % m] += r2[i]) %= mod;
		}
		vector<int> s2 = conv(s, s);
		for(int i = 0; i < s2.size(); ++i){
			(freq[g_pow[(i + 262) % order] * m2 % m] += s2[i]) %= mod;
		}
		vector<int> pq = conv(p, q);
		for(int i = 0; i < pq.size(); ++i){
			(freq[g_pow[i % order] * 17 % m] += 2*pq[i]) %= mod;
		}
		vector<int> pr = conv(p, r);
		for(int i = 0; i < pr.size(); ++i){
			(freq[g_pow[i % order] * m1 % m] += 2*pr[i]) %= mod;
		}
		vector<int> ps = conv(p, s);
		for(int i = 0; i < ps.size(); ++i){
			(freq[g_pow[i % order] * m2 % m] += 2*ps[i]) %= mod;
		}
		vector<int> qr = conv(q, r);
		for(int i = 0; i < qr.size(); ++i){
			(freq[g_pow[(i + 485) % order] * m1 % m] += 2*qr[i]) %= mod;
		}
		vector<int> qs = conv(q, s);
		for(int i = 0; i < qs.size(); ++i){
			(freq[g_pow[(i + 220) % order] * m2 % m] += 2*qs[i]) %= mod;
		}
		freq[0] = (2ll * r_cnt * s_cnt + (lli)z_cnt * z_cnt + 2ll * z_cnt * nz_cnt) % mod;

		vector<int> cnt(m);
		for(int i = 1; i < m; ++i){
			for(int j = i; j < m; j += i){
				cnt[i] += freq[j];
				if(cnt[i] >= mod) cnt[i] -= mod;
			}
		}

		lli ans = 0;
		for(int d = 1; d < m; ++d){
			ans += (lli)mu[d] * cnt[d] * cnt[d] % mod * cnt[d] % mod;
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
		}
		for(int d = 1; d < m; ++d){
			ans += (lli)mu[d] * 3 * freq[0] % mod * cnt[d] % mod * cnt[d] % mod;
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
		}
		ans += 3ll * freq[0] * freq[0] % mod * freq[1] % mod;
		if(ans >= mod) ans -= mod;
		cout << ans << "\n";
	}
	return 0;
}