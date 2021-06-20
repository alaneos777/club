#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353, g = 3;
using poly = vector<int>;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

void ntt(poly& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n-1; ++i){
		for(int k = n>>1; (j^=k) < k; k>>=1);
		if(i < j) swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz <<= 1){
		vector<lli> w(sz/2, 1);
		lli w_1 = powerMod(g, (mod-1)/sz);
		if(inv == -1) w_1 = powerMod(w_1, mod-2);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w_1 * w[j-1] % mod;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = w[j] * a[start + sz/2 + j] % mod;
				a[start + j] = (u+v >= mod ? u+v-mod : u+v);
				a[start + sz/2 + j] = (u-v < 0 ? u-v+mod : u-v);
			}
		}
	}
	if(inv == -1){
		lli n_inv = powerMod(n, mod-2);
		for(int& ai : a){
			ai = n_inv * ai % mod;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	poly P(m+1);
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		P[ai] = 1;
	}
	poly ans = P;
	int SZ = nearestPowerOfTwo(2*m+1);
	P.resize(SZ);
	ntt(P);
	for(int& pi : P){
		pi = (lli)pi * pi % mod;
	}
	ntt(P, -1);
	for(int i = 1; i <= m; ++i){
		if(P[i] > 0){
			if(ans[i] == 0){
				cout << "NO\n";
				return 0;
			}else{
				ans[i] = 0;
				n--;
			}
		}
	}
	cout << "YES\n";
	cout << n << "\n";
	for(int i = 1; i <= m; ++i){
		if(ans[i]) cout << i << " ";
	}
	cout << "\n";
	return 0;
}