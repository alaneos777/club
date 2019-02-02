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

const int p = 998244353;
const int root = 31;
const int root_1 = inverse(root, p);
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
			wk = (lli)wk * wk % p;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0, w = 1; j < k; ++j, w = (lli)w * wk % p){
				int u = X[i + j], v = (lli)X[i + j + k] * w % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
		}
	}
	if(inv == -1){
		int nrev = inverse(n, p);
		for(int i = 0; i < n; ++i)
			X[i] = (lli)X[i] * nrev % p;
	}
}

void convolution(vector<int> & A, vector<int> & B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt(A, 1), ntt(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt(A, -1);
	A.resize(sz);
}

using LL = __int128;

const LL mod = 3 + 1000000000000000000ll;
const LL x0 = 31;
const LL invx0 = inverse(x0, mod);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int k, caso = 1;
	while(cin >> k && k != -1){
		string strA, strB;
		cin >> strA >> strB;
		int m = strA.size(), n = strB.size();
		if(n > m){
			cout << "Case " << caso++ << ": 0\n";
			continue;
		}
		vector<LL> hash(m), x0_pw(m, 1);
		for(int i = 0; i < m; ++i){
			if(i) x0_pw[i] = x0_pw[i-1] * x0 % mod;
			hash[i] = ((i ? hash[i-1] : 0) + (LL)(strA[i]-'a'+1) * x0_pw[i] % mod) % mod;
		}
		vector<int> ans(m - n + 1);
		reverse(strB.begin(), strB.end());
		for(char c : {'a', 'b'}){
			vector<int> P(m), Q(n);
			int freq = 0;
			for(int i = 0; i < m; ++i){
				P[i] = (strA[i] == c);
			}
			for(int i = 0; i < n; ++i){
				freq += (strB[i] == c);
				Q[i] = (strB[i] == c);
			}
			convolution(P, Q);
			for(int i = 0; i <= m-n; ++i){
				ans[i] += freq - P[i+n-1];
			}
		}
		set<LL> hashes;
		for(int i = 0; i <= m-n; ++i){
			if(ans[i] <= k){
				LL h = (hash[i+n-1] - (i ? hash[i-1] : 0)) * inverse(x0_pw[i], mod) % mod;
				if(h < 0) h += mod;
				hashes.insert(h);
				//cout << i << " " << strA.substr(i, n) << " " << ans[i] << " " << h << "\n"; //[i, i+n-1]
			}
		}
		cout << "Case " << caso++ << ": " << hashes.size() << "\n";
	}
	return 0;
}