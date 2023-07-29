#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli sqrtMod(lli a){
	a %= mod;
	if(a < 0) a += mod;
	if(a == 0) return 0;
	if(powerMod(a, (mod - 1) / 2) != 1) return 0;
	if(mod % 4 == 3) return powerMod(a, (mod + 1) / 4);
	lli s = mod - 1;
	int r = 0;
	while((s & 1) == 0) ++r, s >>= 1;
	lli n = 2;
	while(powerMod(n, (mod - 1) / 2) != mod - 1) ++n;
	lli x = powerMod(a, (s + 1) / 2);
	lli b = powerMod(a, s);
	lli g = powerMod(n, s);
	while(true){
		lli t = b;
		int m = 0;
		for(; m < r; ++m){
			if(t == 1) break;
			t = t * t % mod;
		}
		if(m == 0) return x;
		lli gs = powerMod(g, 1 << (r - m - 1));
		g = gs * gs % mod;
		x = x * gs % mod;
		b = b * g % mod;
		r = m;
	}
}

lli R, sqrtR;

struct num{
	lli p, q;

	num(): p(0), q(0) {}
	num(lli p): p(p), q(0) {}
	num(lli p, lli q): p(p), q(q) {
		if(sqrtR != 0){
			this->p = (this->p + this->q*sqrtR) % mod;
			this->q = 0;
		}
	}

	num operator+(const num& rhs) const{
		lli new_p = p + rhs.p; if(new_p >= mod) new_p -= mod;
		lli new_q = q + rhs.q; if(new_q >= mod) new_q -= mod;
		return num(new_p, new_q);
	}

	num operator-(const num& rhs) const{
		lli new_p = p - rhs.p; if(new_p < 0) new_p += mod;
		lli new_q = q - rhs.q; if(new_q < 0) new_q += mod;
		return num(new_p, new_q);
	}

	num operator*(const num& rhs) const{
		lli new_p = (p * rhs.p + q * rhs.q % mod * R) % mod;
		lli new_q = (p * rhs.q + q * rhs.p) % mod;
		return num(new_p, new_q);
	}

	num operator/(const num& rhs) const{
		lli new_p = (p * rhs.p - q * rhs.q % mod * R) % mod; if(new_p < 0) new_p += mod;
		lli new_q = (q * rhs.p - p * rhs.q) % mod; if(new_q < 0) new_q += mod;
		lli den = (rhs.p * rhs.p - rhs.q * rhs.q % mod * R) % mod; if(den < 0) den += mod;
		lli inv_den = powerMod(den, mod-2);
		return num(new_p * inv_den % mod, new_q * inv_den % mod);
	}

	num operator^(lli b) const{
		num ans = 1, a = *this;
		while(b){
			if(b&1) ans = ans * a;
			b >>= 1;
			a = a * a;
		}
		return ans;
	}

	bool operator==(const num& rhs) const{
		return p == rhs.p && q == rhs.q;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int k;
		lli a, b, x, y, n;
		cin >> a >> b >> x >> y >> n >> k;
		if(a == 0 && b == 0){
			if(n == 0) cout << powerMod(x, k) << "\n";
			else if(n >= 1) cout << (powerMod(x, k) + powerMod(y, k)) % mod << "\n";
			continue;
		}
		R = a*a + 4*b;
		sqrtR = sqrtMod(R);
		vector<vector<num>> C(3, vector<num>(max(2, k+1), 1));
		vector<vector<num>> Z(3, vector<num>(max(2, k+1), 1));
		Z[1][1] = num(a, 1) / 2;
		Z[2][1] = num(a, mod-1) / 2;
		C[1][1] = ((num)y - Z[2][1]*x) / (Z[1][1] - Z[2][1]);
		C[2][1] = (Z[1][1]*x - y) / (Z[1][1] - Z[2][1]);
		for(int i = 1; i <= k; ++i){
			for(int j = 1; j <= 2; ++j){
				C[j][i] = C[j][i-1] * C[j][1];
				Z[j][i] = Z[j][i-1] * Z[j][1];
			}
		}
		num ans = 0;
		lli comb = 1;
		for(int i = 0; i <= k; ++i){
			num ratio = Z[1][i] * Z[2][k-i];
			if(ratio == 1){
				ans = ans + (num)comb * C[1][i] * C[2][k-i] * ((n+1) % mod);
			}else{
				ans = ans + (num)comb * C[1][i] * C[2][k-i] * ((ratio^(n+1)) - 1) / (ratio - 1);
			}
			comb = comb * (k - i) % mod * powerMod(i + 1, mod-2) % mod;
		}
		cout << ans.p << "\n";
	}
	return 0;
}