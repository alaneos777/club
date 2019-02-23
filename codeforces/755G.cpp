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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n; int k;
	cin >> n >> k;
	int m = k+10;
	int sz = nearestPowerOfTwo(2*m-1);
	lli pw = 1;
	vector<vector<int>> z(2, vector<int>(sz));
	z[0][0] = 1;
	for(lli v = n; v >>= 1; pw <<= 1);
	do{
		int d = (n & pw) != 0;
		vector<vector<int>> C(4, vector<int>(sz));
		ntt(z[0], 1);
		ntt(z[1], 1);
		for(int i = 0; i < sz; ++i){
			C[d][i] = (lli)z[0][i] * z[0][i] % p;
			C[d+1][i] = (lli)z[0][i] * z[1][i] % p * 2ll % p;
			C[d+2][i] = (lli)z[1][i] * z[1][i] % p;
		}
		ntt(C[d], -1);
		ntt(C[d+1], -1);
		ntt(C[d+2], -1);
		fill(z[0].begin(), z[0].end(), 0);
		fill(z[1].begin(), z[1].end(), 0);
		for(int i = 0; i < m; ++i){
			z[1][i] = ((lli)C[3][i] + C[2][i] + C[1][i]) % p;
			z[0][i] = C[0][i];
		}
		for(int i = 0; i < m-1; ++i){
			z[1][i+1] = ((lli)z[1][i+1] + 3ll*C[3][i] + C[2][i]) % p;
			z[0][i+1] = ((lli)z[0][i+1] + C[3][i] + C[2][i]) % p;
		}
		for(int i = 0; i < m-2; ++i){
			z[1][i+2] = ((lli)z[1][i+2] + C[3][i]) % p;
			z[0][i+2] = ((lli)z[0][i+2] + C[3][i]) % p;
		}
	}while(pw >>= 1);
	vector<int> ans(m);
	for(int i = 0; i < m; ++i){
		ans[i] = ((lli)z[0][i] + z[1][i]) % p;
	}
	for(int i = 0; i < m-1; ++i){
		ans[i+1] = ((lli)ans[i+1] + z[1][i]) % p;
	}
	for(int i = 1; i <= k; ++i){
		cout << ans[i] << " ";
	}
	cout << "\n";
	return 0;
}