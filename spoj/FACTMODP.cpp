#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using LLI = __int128;

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(abs(r0) == 1);
	if(r0 == -1) r0 *= -1, s0 *= -1;
	if(s0 < 0) s0 += n;
	return s0;
}

lli nearestPowerOfTwo(lli n){
	lli ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

LLI powerMod(LLI b, LLI e, LLI m){
	LLI ans = 1;
	e %= m-1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

template<lli prime, lli gen>
void ntt(vector<lli> & X, lli inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<LLI> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		LLI wk = powerMod(gen, inv * (prime - 1) / (k<<1), prime);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % prime;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				lli u = X[i + j], v = X[i + j + k] * wp[j] % prime;
				X[i + j] = u + v < prime ? u + v : u + v - prime;
				X[i + j + k] = u - v < 0 ? u - v + prime : u - v;
			}
		}
	}
	if(inv == -1){
		LLI nrev = inverse(n, prime);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % prime;
	}
}

template<lli prime, lli gen>
vector<lli> convolution(vector<lli> A, vector<lli> B){
	int size = A.size();
	ntt<prime, gen>(A, 1), ntt<prime, gen>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (LLI)A[i] * B[i] % prime;
	ntt<prime, gen>(A, -1);
	return A;
}

const lli a = 8220835841ll, b = 8279556097ll, c = 8304721921ll;
const LLI a_b = inverse(a, b), a_c = inverse(a, c), b_c = inverse(b, c);
vector<lli> conv(const vector<lli> & A, const vector<lli> & B, lli mod){
	vector<lli> P = convolution<a, 3>(A, B);
	vector<lli> Q = convolution<b, 5>(A, B);
	vector<lli> R = convolution<c, 7>(A, B);
	vector<lli> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		lli x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		lli x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		lli x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 + a*(x2 + (LLI)x3*b % mod) % mod;
		if(D[i] >= mod) D[i] -= mod;
		if(D[i] < 0) D[i] += mod;
	}
	return D;
}

const int M = 1e6 + 10;
vector<lli> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);

vector<lli> interpolateNext(const vector<lli> & firstHalf, lli mod){
	int n = (int)firstHalf.size() - 1;
	int sz = nearestPowerOfTwo(2*n+1);
	vector<lli> P(sz), Q(sz);
	for(int i = 0; i <= n; ++i){
		P[i] = (LLI)firstHalf[i] * invfact[i] % mod * invfact[n-i] % mod;
		if(i & 1) P[i] = (mod - P[i]) % mod;
	}
	for(int i = 0; i <= n; ++i){
		Q[i] = inv[n+1+i];
		if(i) Q[sz-i] = inv[n+1-i];
	}
	vector<lli> secondHalf = conv(P, Q, mod);
	for(int x = 0; x <= n; ++x){
		secondHalf[x] = (LLI)secondHalf[x] * fact[x+n+1] % mod * invfact[x] % mod;
		if(n & 1) secondHalf[x] = (mod - secondHalf[x]) % mod;
	}
	vector<lli> ans;
	copy(firstHalf.begin(), firstHalf.end(), back_inserter(ans));
	copy(secondHalf.begin(), secondHalf.begin()+n+1, back_inserter(ans));
	return ans;
}

vector<lli> interpolateHalf(const vector<lli> & firstHalf, lli d, lli mod){
	int n = (int)firstHalf.size() - 1;
	int a = n/2;
	int sz = nearestPowerOfTwo(2*n+1);
	vector<lli> P(sz), Q(sz);
	for(int i = 0; i <= n; ++i){
		P[i] = (LLI)firstHalf[i] * invfact[i] % mod * invfact[n-i] % mod;
		if(i & 1) P[i] = (mod - P[i]) % mod;
	}
	for(int i = 0; i <= n; ++i){
		Q[i] = (LLI)d * inverse(a + d*i, mod) % mod;
		if(i) Q[sz-i] = (LLI)d * inverse(a - d*i, mod) % mod;
	}
	vector<lli> secondHalf = conv(P, Q, mod);
	lli window = 1;
	for(int i = 0; i <= n; ++i){
		window = (LLI)window * (a - d*i) % mod * inv[d] % mod;
		if(window < 0) window += mod;
	}
	for(int x = 0; x <= n; ++x){
		secondHalf[x] = (LLI)secondHalf[x] * window % mod;
		if(n & 1) secondHalf[x] = (mod - secondHalf[x]) % mod;
		window = (LLI)window * (a + d*(x+1)) % mod * inverse(a - d*n + d*x, mod) % mod;
		if(window < 0) window += mod;
	}
	secondHalf.resize(n+1);
	return secondHalf;
}

//let P_n(x)=(x+1)(x+2)...(x+n)
//it finds P_n(0), P_n(d), ..., P_n(nd)
vector<lli> solve(lli n, lli d, lli mod){
	if(n == 1) return vector<lli>{1, (d+1) % mod};
	auto partial = solve(n/2, d, mod); //length: floor(n/2)+1
	vector<lli> lhs = interpolateNext(partial, mod); //length: 2floor(n/2)+2
	vector<lli> rhs = interpolateHalf(lhs, d, mod); //length: 2floor(n/2)+2
	vector<lli> ans(n+1);
	for(int i = 0; i <= n; ++i){
		ans[i] = (LLI)lhs[i] * rhs[i] % mod;
		if(n & 1){
			ans[i] = (LLI)ans[i] * (n + d*i) % mod;
		}
	}
	return ans;
}

lli naive(lli n, lli mod){
	lli ans = 1;
	for(lli i = 1; i <= n; ++i){
		ans = (LLI)ans * i % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n, mod;
		cin >> n >> mod;
		if(n >= mod){
			cout << "0\n";
			continue;
		}
		if(n == 0){
			cout << "1\n";
			continue;
		}
		if(n <= 10000){
			cout << naive(n, mod) << "\n";
			continue;
		}
		lli d = sqrt(n);
		lli limit = 3*d + 1;
		for(lli i = 2; i <= limit; ++i){
			fact[i] = (LLI)fact[i-1] * i % mod;
		}
		for(lli i = 2; i <= limit && i < mod; ++i){
			inv[i] = mod - (LLI)(mod / i) * inv[mod % i] % mod;
			invfact[i] = (LLI)invfact[i-1] * inv[i] % mod;
		}
		auto arr = solve(d, d, mod);
		lli ans = 1;
		for(int i = 0; i < d; ++i){
			ans = (LLI)ans * arr[i] % mod;
		}
		for(lli i = d*d+1; i <= n; ++i){
			ans = (LLI)ans * i % mod;
		}
		cout << ans << "\n";
	}
	return 0;
}