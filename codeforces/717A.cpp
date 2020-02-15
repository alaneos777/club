#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<lli> mul(const vector<lli> & a, const vector<lli> & b, const vector<lli> & m){
	vector<lli> c(2);
	c[0] = a[0] * b[0] % mod;
	c[1] = (a[0] * b[1] % mod + a[1] * b[0] % mod) % mod;
	lli c2 = a[1] * b[1] % mod;
	(c[1] += c2*m[1]) %= mod;
	(c[0] += c2*m[0]) %= mod;
	return c;
}

vector<lli> power(vector<lli> a, lli n, const vector<lli> & m){
	vector<lli> ans(2); ans[0] = 1;
	while(n){
		if(n & 1) ans = mul(ans, a, m);
		n >>= 1;
		a = mul(a, a, m);
	}
	return ans;
}

struct num{
	lli a, b;
	num(): a(0), b(0) {}
	num(lli a): a(a), b(0) {}
	num(lli a, lli b): a(a), b(b) {}
	num operator+(const num & rhs) const{return num((a + rhs.a) % mod, (b + rhs.b) % mod);}
	num operator-(const num & rhs) const{return num(((a - rhs.a) % mod + mod) % mod, ((b - rhs.b) % mod + mod) % mod);}
	num operator*(const lli & k) const{return num(a * k % mod, b * k % mod);}
	num operator/(const lli & k) const{
		lli rev = power(k, mod-2);
		return num(a * rev % mod, b * rev % mod);
	}
	num operator*(const num & rhs) const{
		lli A = (a*rhs.a%mod + 5*b*rhs.b%mod) % mod;
		lli B = (a*rhs.b%mod + b*rhs.a%mod) % mod;
		return num(A, B);
	}
	num operator/(const num & rhs) const{
		lli den = ((rhs.a*rhs.a%mod - 5*rhs.b*rhs.b%mod) % mod + mod) % mod;
		return num(a, b) * num(rhs.a, (-rhs.b+mod)%mod) / den;
	}
	num operator^(const lli & n) const{
		auto pol = power({0, 1}, n, {((5*b*b%mod - a*a%mod) % mod + mod) % mod, 2*a%mod});
		return num((a*pol[1]%mod + pol[0]) % mod, b*pol[1]%mod);
	}
	bool operator==(const num & rhs) const{return a==rhs.a && b==rhs.b;}
};

const num x = num(power(2, mod-2), power(2, mod-2));
const num y = num(power(2, mod-2), mod-power(2, mod-2));

const int M = 250;

lli ncr[M+1][M+1];

vector<lli> mult_pol(const vector<lli> & a, const vector<lli> & b){
	vector<lli> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			(c[i+j] += a[i] * b[j]) %= mod;
		}
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ncr[0][0] = 1;
	for(int i = 1; i <= M; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % mod;
		}
	}
	int k; lli l, r;
	cin >> k >> l >> r;
	vector<lli> stirling(1, 1);
	for(int i = 0; i < k; ++i){
		stirling = mult_pol(stirling, {(-i+mod) % mod, 1ll});
	}

	auto T = [&](int j, lli n){
		num ans = 0;
		num down = x^j;
		num down_delta = y/x;
		num up = down^(n+3);
		num up_delta = down_delta^(n+3);
		int alt = 1;
		for(int r = 0; r <= j; ++r){
			if(down == 1){
				ans = ans + ((n+3)%mod) * ncr[j][r] % mod * alt % mod;
			}else{
				ans = ans + (up - 1) / (down - 1) * ncr[j][r] * alt;
			}
			up = up * up_delta;
			down = down * down_delta;
			alt = mod - alt;
		}
		if(j & 1){
			ans = ans / num(0, power(5, j/2));
		}else{
			ans = ans / num(power(5, j/2), 0);
		}
		return (ans - 1).a;
	};

	lli ans = 0;
	for(int j = 1; j <= k; ++j){
		(ans += stirling[j] * (T(j, r) - T(j, l-1))) %= mod;
	}
	for(int i = 1; i <= k; ++i){
		ans = ans * power(i, mod-2) % mod;
	}
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}