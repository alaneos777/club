/*
https://www.jaapsch.net/puzzles/lomath.htm#fibpoly
https://www.win.tue.nl/~aeb/ca/madness/madrect.html
https://www.win.tue.nl/~aeb/ca/madness/madrect2.html
*/

#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
using poly = vector<bool>;

void clean(poly & p){
	while(!p.empty() && p.back() == 0) p.pop_back();
	if(p.empty()) p.push_back(0);
}

poly operator+(const poly & a, const poly & b){
	poly c(max(a.size(), b.size()));
	for(int i = 0; i < c.size(); ++i){
		c[i] = (i < a.size() ? a[i] : 0) ^ (i < b.size() ? b[i] : 0);
	}
	clean(c);
	return c;
}

poly operator*(const poly & a, const poly & b){
	poly c((int)a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] = c[i+j] ^ (a[i] & b[j]);
		}
	}
	clean(c);
	return c;
}

poly operator%(const poly & a, const poly & b){
	poly r = a;
	while(r.size() >= b.size() && !(r.size() == 1 && r[0] == 0)){
		size_t g = r.size() - b.size();
		for(int i = 0; i < b.size(); ++i){
			r[i+g] = r[i+g] ^ b[i];
		}
		clean(r);
	}
	return r;
}

poly GCD(poly a, poly b){
	while(!(b.size() == 1 && b[0] == 0)){
		poly r = a % b;
		a = b, b = r;
	}
	return a;
}

poly shift(const poly & a){
	poly p_pow = {1};
	poly c = {0};
	for(int i = 0; i < a.size(); ++i){
		if(a[i]){
			c = c + p_pow;
		}
		p_pow = p_pow * poly{1, 1};
	}
	clean(c);
	return c;
}

struct int256_t{
	__uint128_t lo, hi;
	int256_t(): lo(0), hi(0){}
	int256_t(__uint128_t x): lo(x), hi(0){}
	int256_t(__uint128_t x, __uint128_t y): lo(x), hi(y){}
	int256_t operator+(const int256_t & rhs) const{
		__uint128_t a = lo + rhs.lo;
		__uint128_t b = hi + rhs.hi + (a < lo);
		return int256_t(a, b);
	}
	int256_t operator&(const int256_t & rhs) const{return int256_t(lo & rhs.lo, hi & rhs.hi);}
	int256_t& operator>>=(int n){
		lo = (lo >> 1) | ((hi & 1) << 127);
		hi >>= 1;
		return *this;
	}
	int256_t& operator<<=(int n){
		hi = (hi << 1) | (lo >> 127);
		lo <<= 1;
		return *this;
	}
	bool z() const{return lo == 0 && hi == 0;}
};

poly rec(const vector<poly> & P, const vector<poly> & init, const poly & modulo, int256_t n){
	int deg = P.size();
	vector<poly> ans(deg, poly{0}), R(2*deg, poly{0});
	ans[0] = {1};
	int256_t p = 1;
	for(int256_t v = n; !(v >>= 1).z(); p <<= 1);
	do{
		int d = !((n & p).z());
		fill(R.begin(), R.end(), poly{0});
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] = (R[i + j + d] + ans[i] * ans[j]) % modulo;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				R[i + j] = (R[i + j] + R[i + deg] * P[j]) % modulo;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(!(p >>= 1).z());
	poly nValue = {0};
	for(int i = 0; i < deg; i++)
		nValue = (nValue + ans[i] * init[i]) % modulo;
	return nValue;
}

lli power(lli a, lli b, lli mod){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli f(int w, int256_t h){
	vector<poly> c = {{1}, {0, 1}};
	while(c.size() <= w){
		c.push_back(c[c.size()-1] * poly{0, 1} + c[c.size()-2]);
	}
	poly A = shift(c[w]);
	poly B = rec({{1}, {0, 1}}, {{1}, {0, 1}}, A, h);
	int nullity = (int)GCD(A, B).size() - 1;
	lli H = (h.lo % (mod-1) + h.hi % (mod-1) * power(2, 128, mod-1)) % (mod-1);
	lli rank = w*H % (mod-1) - nullity % (mod-1);
	if(rank < 0) rank += mod-1;
	return power(2, rank, mod);
}

int main(){
	int m = 199, n = 199;
	vector<int256_t> fib = {0, 1};
	while(fib.size() <= n){
		fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
	}
	lli ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += f(m, fib[i]);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}