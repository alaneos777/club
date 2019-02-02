#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int inverse(int a, int n){
	int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

const int p = 998244353;
const int root = 31;
const int root_1 = inverse(root, p);
const int root_pw = 1 << 23;

void ntt(vector<int> & X, int inv){
	int n = X.size();
	int len, len2, wlen, i, j, k, u, v, w;
	for(i = 1, j = 0; i < n - 1; ++i){
		for(k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(len = 2; len <= n; len <<= 1){
		len2 = len >> 1;
		wlen = (inv == -1) ? root_1 : root;
		for(i = len; i < root_pw; i <<= 1){
			wlen = (lli)wlen * wlen % p;
		}
		for(i = 0; i < n; i += len){
			w = 1;
			for(j = 0; j < len2; ++j){
				u = X[i + j], v = (lli)X[i + j + len2] * w % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + len2] = u - v < 0 ? u - v + p : u - v;
				w = (lli)w * wlen % p;
			}
		}
	}
	if(inv == -1){
		int nrev = inverse(n, p);
		for(i = 0; i < n; ++i){
			X[i] = (lli)X[i] * nrev % p;
		}
	}
}

void square(vector<int> & A){
	int degree = A.size() + A.size() - 2;
	int size = nearestPowerOfTwo(degree + 1);
	A.resize(size);
	ntt(A, 1);
	for(int i = 0; i < size; i++){
		A[i] = (lli)A[i] * A[i] % p;
	}
	ntt(A, -1);
	A.resize(degree + 1);
}

void convolution(vector<int> & A, vector<int> B){
	int degree = A.size() + B.size() - 2;
	int size = nearestPowerOfTwo(degree + 1);
	A.resize(size);
	B.resize(size);
	ntt(A, 1);
	ntt(B, 1);
	for(int i = 0; i < size; i++){
		A[i] = (lli)A[i] * B[i] % p;
	}
	ntt(A, -1);
	A.resize(degree + 1);
}

void adjust(vector<int> & A, int period){
	for(int i = period; i < A.size(); ++i){
		A[i-period] = (A[i-period] + A[i]) % p;
	}
	A.resize(period);
}

vector<int> primes;

void linearPrimeSieve(int n){
	vector<bool> isPrime(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(isPrime[i])
			primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
}

vector<pair<lli, int>> factorize(lli n){
	vector<pair<lli, int>> f;
	for(lli p : primes){
		if(p * p > n) break;
		int pot = 0;
		while(n % p == 0){
			pot++;
			n /= p;
		}
		if(pot) f.emplace_back(p, pot);
	}
	if(n > 1) f.emplace_back(n, 1);
	return f;
}

lli phi(lli n){
	lli ans = n;
	auto f = factorize(n);
	for(auto & factor : f)
		ans -= ans / factor.first;
	return ans;
}

lli findFirstGenerator(lli m){
	lli order = phi(m);
	auto f = factorize(order);
	for(lli x = 1; x < m; x++){
		if(__gcd(x, m) != 1) continue;
		bool test = true;
		for(auto & factor : f){
			lli p = factor.first;
			if(powerMod(x, order / p, m) == 1){
				test = false;
				break;
			}
		}
		if(test) return x;
	}
	return -1; //not found
}

int main(){
	linearPrimeSieve(1e5);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, mod, k;
	cin >> n >> mod >> k;
	int g = findFirstGenerator(mod);
	int acum = 1;
	int i = 0;
	vector<int> index(mod);
	do{
		index[acum] = i++;
		acum = (lli)acum * g % mod;
	}while(acum != 1);
	assert(i == mod-1);
	vector<int> a(n);
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		a[i] = index[a[i]];
	}

	vector<int> P(mod-1);
	for(int i = 0; i < n; ++i){
		P[a[i]]++;
	}
	vector<int> Q(mod-1);
	Q[0] = 1;
	int t = 1;
	for(int v = k; v >>= 1; t <<= 1);
	do{
		square(Q);
		adjust(Q, mod - 1);
		if((k & t) != 0) convolution(Q, P);
		adjust(Q, mod - 1);
	}while(t >>= 1);

	int ans = 0;
	acum = 1;
	for(int i = 0; i < mod-1; ++i){
		ans = (ans + (lli)acum * Q[i]) % p;
		acum = (lli)acum * g % mod;
	}
	ans = (lli)ans * powerMod(n, ((p-1-k)%(p-1)+p-1)%(p-1), p) % p;
	cout << ans << "\n";
	return 0;
}