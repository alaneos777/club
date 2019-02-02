#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

vector<bool> sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	isPrime[1] = false;
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
	return isPrime;
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

const int p = 1004535809;
const int root = 4172;
const int root_1 = inverse(root, p);
const int root_pw = 1 << 21;

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<bool> isPrime = sieve(1e6);
	int n, k;
	cin >> n >> k;
	clock_t start = clock();
	vector<int> cnt(n + 1);
	cnt[0] = 1;
	int idx = 0, i = 2;
	while(idx <= n){
		if(isPrime[i]) idx++;
		cnt[idx]++;
		i++;
	}
	vector<int> res(n + 1);
	res[0] = 1;
	int t = 1;
	for(int v = k; v >>= 1; t <<= 1);
	do{
		square(res);
		res.resize(n + 1);
		if((k & t) != 0) convolution(res, cnt);
		res.resize(n + 1);
	}while(t >>= 1);
	cout << res[n] << "\n";
	cout << fixed << setprecision(3) << (double)(clock() - start)/(double)CLOCKS_PER_SEC << "s\n";
	return 0;
}