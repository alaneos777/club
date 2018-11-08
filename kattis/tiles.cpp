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

const int p = 167772161;
const int root = 4;
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

template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
	}

	void build(){
		for(int i = N - 1; i > 0; --i)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}

	T query(int l, int r){
		T res = make_pair(numeric_limits<int>::min(), 0);
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res = max(res, ST[l++]);
			if(!(r & 1)) res = max(ST[r--], res);
		}
		return res;
	}
};

const int M = 5e5 + 10;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> divs(M + 1);
	for(int i = 1; i <= M; ++i)
		for(int j = i; j <= M; j += i)
			++divs[j];
	int degree = divs.size() + divs.size() - 2;
	int size = nearestPowerOfTwo(degree + 1);
	divs.resize(size);
	ntt(divs, 1);
	for(int i = 0; i < size; i++){
		divs[i] = (lli)divs[i] * divs[i] % p;
	}
	ntt(divs, -1);
	divs.resize(M + 1);
	SegmentTree<pair<int, int>> st(M + 1);
	for(int i = 0; i <= M; ++i)
		st.ST[M + 1 + i] = make_pair(divs[i], -i);
	st.build();
	int n, l, r;
	cin >> n;
	while(n--){
		cin >> l >> r;
		int a, ways;
		tie(ways, a) = st.query(l, r);
		cout << -a << " " << ways << "\n";
	}
	return 0;
}