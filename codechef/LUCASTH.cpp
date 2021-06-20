#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
using poly = vector<int>;

template<lli mod>
lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

template<int mod, int g>
void ntt(poly& a, int inv = 1){
	int n = a.size();
	for(int i = 1, j = 0; i < n-1; ++i){
		for(int k = n>>1; (j^=k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz <<= 1){
		lli w_1 = powerMod<mod>(g, (mod-1)/sz);
		if(inv == -1) w_1 = powerMod<mod>(w_1, mod-2);
		vector<lli> w(sz/2, 1);
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
		lli n_rev = powerMod<mod>(n, mod-2);
		for(int& ai : a){
			ai = ai * n_rev % mod;
		}
	}
}

template<int mod, int g>
poly conv(poly a, poly b){
	int sz = a.size() + b.size() - 1;
	int SZ = nearestPowerOfTwo(sz);
	a.resize(SZ), b.resize(SZ);
	ntt<mod, g>(a, 1), ntt<mod, g>(b, 1);
	poly c(SZ);
	for(int i = 0; i < SZ; ++i){
		c[i] = (lli)a[i] * b[i] % mod;
	}
	ntt<mod, g>(c, -1);
	c.resize(sz);
	return c;
}

const int a = 998244353, b = 985661441;
const lli a_b = powerMod<b>(a, b-2);
vector<int> conv_mod(const vector<int> & A, const vector<int> & B, int mod){
	vector<int> P = conv<a, 3>(A, B);
	vector<int> Q = conv<b, 3>(A, B);
	vector<int> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		int x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		int x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		D[i] = x1 % mod + (lli)a*x2 % mod;
		if(D[i] >= mod) D[i] -= mod;
	}
	return D;
}

poly conv_ten(int b){
	poly ans;
	int t = 10;
	while(t){
		ans.push_back(t % b);
		t /= b;
	}
	return ans;
}

void carry(poly& p, int b){
	int c = 0;
	for(int i = 0; i < p.size(); ++i){
		p[i] += c;
		c = p[i] / b;
		p[i] %= b;
	}
	while(c){
		p.push_back(c%b);
		c /= b;
	}
}

poly mult_sq(const poly& a, const poly& b){
	if(a.empty() || b.empty()) return {0};
	int m = a.size(), n = b.size();
	vector<int> c(m+n-1);
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		string n; int p;
		cin >> n >> p;
		int d = n.size();
		poly ten = conv_ten(p);
		poly number;
		for(int i = 0; i < d; ++i){
			number = mult_sq(number, ten);
			number[0] += n[i]-'0';
			carry(number, p);
		}
		int res = number[0];
		number.erase(number.begin());
		if(res == p-1){
			res = 0;
			number[0]++;
			carry(number, p);
		}
		lli ans = 1;
		for(int i = 0; i < number.size(); ++i){
			ans = ans * (number[i] + 1) % mod;
		}
		function<poly(int, int)> mult = [&](int l, int r){
			if(l == r) return poly{l, 1};
			int m = (l+r)/2;
			return conv_mod(mult(l, m), mult(m+1, r), p);
		};
		poly P = (res == 0 ? poly{1} : mult(1, res));
		int non_zero = 0;
		for(int pi : P){
			non_zero += (pi != 0);
		}
		ans = ans * non_zero % mod;
		cout << ans << "\n";
	}
	return 0;
}