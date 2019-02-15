#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

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

const int mod = (105<<23) + 1;
const int root = 211;
const int root_1 = inverse(root, mod);
const int root_pw = 1 << 23;

void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	for(int k = 1; k < n; k <<= 1){
		int wk = (inv == -1) ? root_1 : root;
		for(int i = k << 1; i < root_pw; i <<= 1)
			wk = (lli)wk * wk % mod;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0, w = 1; j < k; ++j, w = (lli)w * wk % mod){
				int u = X[i + j], v = (lli)X[i + j + k] * w % mod;
				X[i + j] = u + v < mod ? u + v : u + v - mod;
				X[i + j + k] = u - v < 0 ? u - v + mod : u - v;
			}
		}
	}
	if(inv == -1){
		int nrev = inverse(n, mod);
		for(int i = 0; i < n; ++i)
			X[i] = (lli)X[i] * nrev % mod;
	}
}

void convolution(vector<int> & A, vector<int> & B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt(A, 1), ntt(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % mod;
	ntt(A, -1);
	A.resize(sz);
}

struct SegmentTree{
	SegmentTree *left, *right;
	int l, r;
	int sum;
	bool flip;
 
	SegmentTree(int start, int end): left(NULL), right(NULL), l(start), r(end), sum(0), flip(false){
		if(l == r) sum = 1;
		else{
			int half = l + ((r - l) >> 1);
			left = new SegmentTree(l, half);
			right = new SegmentTree(half+1, r);
			sum = left->sum + right->sum;
		}
	}
 
	void propagate(){
		sum = (r - l + 1) - sum;
		if(l != r){
			left->flip ^= true;
			right->flip ^= true;
		}
	}
 
	int active(int start, int end){
		if(flip){
			propagate();
			flip = false;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum;
		else return left->active(start, end) + right->active(start, end);
	}
 
	void flip_range(int start, int end){
		if(flip){
			propagate();
			flip = false;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate();
		else{
			left->flip_range(start, end);
			right->flip_range(start, end);
			sum = left->sum + right->sum;
		}
	}
};

lli powerMod(lli a, lli b){
	lli ans = 1;
	a %= mod;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const int M = 1e5 + 100;

int main(){
	vector<lli> inv(M+1, 1), invfact(M+1, 1);
	for(int i = 2; i <= M; ++i){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = invfact[i-1] * inv[i] % mod;
	}
	int t;
	scanf("%d", &t);
	while(t--){
		int n, m, d, l, r;
		scanf("%d %d %d", &n, &m, &d);

		vector<int> p(n), q(n);
		for(int i = 0; i < n; ++i){
			p[i] = powerMod(i, n) * invfact[i] % mod;
			q[i] = invfact[i];
			if(i & 1) q[i] = (mod - q[i]) % mod;
		}
		convolution(p, q);
		p.resize(n);
		p.push_back(1);

		SegmentTree st(0, m-1);
		while(d--){
			scanf("%d %d", &l, &r);
			st.flip_range(l-1, r-1);
			printf("%d\n", p[st.active(0, m-1)]);
		}
	}
	return 0;
}