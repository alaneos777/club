#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;
const lli g = 3;

lli power(lli a, lli b){
	if(b < 0) b += mod-1;
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int near(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

void ntt(vector<int>& a, int inv){
	int n = a.size();
	for(int i = 1, j = 0; i < n-1; ++i){
		for(int k = n>>1; (j^=k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
	vector<lli> w(n>>1, 1);
	for(int sz = 2; sz <= n; sz <<= 1){
		lli w1 = power(g, (mod-1)/sz * inv);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w[j-1] * w1 % mod;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = a[start + j + sz/2] * w[j] % mod;
				a[start + j] = u+v >= mod ? u+v-mod : u+v;
				a[start + j + sz/2] = u-v < 0 ? u-v+mod : u-v;
			}
		}
	}
	if(inv == -1){
		lli n_inv = power(n, -1);
		for(int& ai : a){
			ai = ai * n_inv % mod;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	int sz = 9*n/2+1;
	vector<int> P(near(sz));
	while(k--){
		int d;
		cin >> d;
		P[d]++;
	}
	ntt(P, 1);
	for(int& pi : P){
		pi = power(pi, n/2);
	}
	ntt(P, -1);
	lli ans = 0;
	for(int pi : P){
		(ans += (lli)pi*pi) %= mod;
	}
	cout << ans << "\n";
	return 0;
}