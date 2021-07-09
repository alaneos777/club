/*
https://www.ams.org/journals/jams/2003-16-04/S0894-0347-03-00428-4/S0894-0347-03-00428-4.pdf
https://www.combinatorics.org/ojs/index.php/eljc/article/download/v10i1r36/pdf/
https://arxiv.org/pdf/math/0411444.pdf
*/

#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli mod = 1e9 + 7;

__int128_t floor(__int128_t a, __int128_t b){
	if((a >= 0 && b > 0) || (a < 0 && b < 0)){
		return a / b;
	}else{
		if(a % b == 0) return a / b;
		else return a / b - 1;
	}
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli ext_gcd(lli a, lli b, lli & s, lli & t){
	lli r0 = a, r1 = b, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti, q;
	while(r1){
		q = r0 / r1;
		ri = r0 - r1 * q, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
		ti = t0 - t1 * q, t0 = t1, t1 = ti;
	}
	s = s0, t = t0;
	return r0;
}

auto get(lli a, lli b, lli c){
	lli x0, y0;
	ext_gcd(a, b, x0, y0);
	for(lli r = 1; ; ++r){
		lli sols = floor((__int128_t)x0 * c*r, b) + floor((__int128_t)y0 * c*r, a) + 1;
		if(sols > 0){
			__int128_t k = floor((__int128_t)x0 * c*r, b);
			lli x = (__int128_t)x0 * c*r - b*k;
			lli y = (__int128_t)y0 * c*r + a*k;
			return make_tuple(r, x, y);
		}
	}
}

const int terms = 6;

vector<lli> operator+(const vector<lli> & a, const vector<lli> & b){
	vector<lli> c(terms);
	for(int i = 0; i < a.size() && i < terms; ++i){
		c[i] = a[i];
	}
	for(int i = 0; i < b.size() && i < terms; ++i){
		c[i] += b[i];
		if(c[i] >= mod) c[i] -= mod;
	}
	return c;
}

vector<lli> operator-(const vector<lli> & a, const vector<lli> & b){
	vector<lli> c(terms);
	for(int i = 0; i < a.size() && i < terms; ++i){
		c[i] = a[i];
	}
	for(int i = 0; i < b.size() && i < terms; ++i){
		c[i] -= b[i];
		if(c[i] < 0) c[i] += mod;
	}
	return c;
}

vector<lli> operator*(const vector<lli> & a, const vector<lli> & b){
	vector<lli> c(terms);
	for(int i = 0; i < a.size() && i < terms; ++i){
		for(int j = 0; j < b.size() && j < terms; ++j){
			if(i+j < terms){
				(c[i+j] += a[i]*b[j]) %= mod;
			}
		}
	}
	return c;
}

vector<lli> Exp(lli a){
	vector<lli> e(terms);
	lli inv_fact = 1, a_pw = 1;
	for(int i = 0; i < terms; ++i){
		e[i] = a_pw * inv_fact % mod;
		a_pw = a_pw * a % mod;
		inv_fact = inv_fact * power(i+1, mod-2) % mod;
	}
	return e;
}

vector<lli> operator/(const vector<lli> & a, const vector<lli> & b){
	int off = 0;
	while(a[off] == 0 && b[off] == 0){
		off++;
	}
	assert(b[off] != 0);
	lli inv = power(b[off], mod-2);
	vector<lli> c(terms - off);
	for(int i = 0; i < terms-off; ++i){
		c[i] = a[i+off];
		for(int j = 0; j < i; ++j){
			c[i] -= c[j] * b[i-j+off] % mod;
			if(c[i] < 0) c[i] += mod;
		}
		c[i] = c[i] * inv % mod;
	}
	return c;
}

auto solve(lli a, lli b, lli c){
	auto x = get(b, c, a);
	auto y = get(a, c, b);
	auto z = get(a, b, c);
	lli p = a*get<0>(x) % mod;
	lli q = b*get<0>(y) % mod;
	lli r = c*get<0>(z) % mod;
	lli m = (c*get<2>(y) + a*get<0>(x)) % mod;
	lli n = (b*get<2>(z) + a*get<0>(x)) % mod;
	// m+n = p+q+r
	// F(x) = 1 / (1 - x) - (1 - x^p - x^q - x^r + x^m + x^n) / [(1 - x^a)(1 - x^b)(1 - x^c)]
	// ans(x) = F(exp(x))
	vector<lli> one = {1};
	auto num = (one - Exp(a)) * (one - Exp(b)) * (one - Exp(c)) - (one - Exp(1)) * (one - Exp(p) - Exp(q) - Exp(r) + Exp(m) + Exp(n));
	auto den = (one - Exp(1)) * (one - Exp(a)) * (one - Exp(b)) * (one - Exp(c));
	auto ans = num / den;
	return (ans[1] + ans[0] * (a + b + c) % mod + (a + b + c - 1) * (a + b + c) / 2 % mod) % mod;
}

int main(){
	int k = 6;
	cout << solve(power(17, k), power(19, k), power(23, k)) << "\n";
	return 0;
}