#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const int mod = 998244353, g = 3;

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

void ntt(vector<int>& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz <<= 1){
		lli w_1 = powerMod(g, (mod-1)/sz);
		if(inv == -1) w_1 = powerMod(w_1, mod-2);
		vector<lli> w(sz/2, 1);
		for(int j = 1; j < sz/2; ++j){
			w[j] = w[j-1] * w_1 % mod;
		}
		for(int start = 0; start < n; start += sz){
			for(int j = 0; j < sz/2; ++j){
				int u = a[start + j], v = a[start + sz/2 + j] * w[j] % mod;
				a[start + j] = (u+v >= mod ? u+v-mod : u+v);
				a[start + sz/2 + j] = (u-v < 0 ? u-v+mod : u-v);
			}
		}
	}
	if(inv == -1){
		lli inv_n = powerMod(n, mod-2);
		for(int i = 0; i < n; ++i){
			a[i] = inv_n * a[i] % mod;
		}
	}
}

vector<int> operator*(vector<int> a, vector<int> b){
	int m = a.size(), n = b.size(), sz = m+n-1;
	int SZ = nearestPowerOfTwo(sz);
	a.resize(SZ), b.resize(SZ);
	vector<int> c(SZ);
	ntt(a, 1), ntt(b, 1);
	for(int i = 0; i < SZ; ++i){
		c[i] = (lli)a[i] * b[i] % mod;
	}
	ntt(c, -1);
	c.resize(sz);
	return c;
}

int Ceil(int a, int b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		if(a % b == 0) return a / b;
		else return a / b + 1;
	}else{
		return a / b;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		string s;
		cin >> n >> s;
		vector<int> a(n), b(n);
		for(int i = 0; i < n; ++i){
			a[i] = (s[i] == 'V');
			b[n-1-i] = (s[i] == 'K');
		}
		vector<int> c = a*b;
		c.push_back(0);
		vector<int> ans;
		for(int k = 1; k <= n; ++k){
			bool test = true;
			for(int j = Ceil(1-n, k); k*j <= n; ++j){
				test &= (c[n-1+k*j] == 0);
				if(!test) break;
			}
			if(test) ans.push_back(k);
		}
		cout << ans.size() << "\n";
		for(int ai : ans){
			cout << ai << " ";
		}
		cout << "\n";
	}
	return 0;
}