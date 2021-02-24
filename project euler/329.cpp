#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

struct frac{
	ll num, den;
	frac(){
		num = 0, den = 1;
	}
	frac(ll x, ll y){
		if(y < 0)
			x *= -1, y *=-1;
		ll d = __gcd(abs(x), abs(y));
		num = x/d, den = y/d;
	}
	frac(ll v){
		num = v;
		den = 1;
	}
	frac operator+(const frac& f) const{
		ll d = __gcd(den, f.den);
		return frac(num*(f.den/d) + f.num*(den/d), den*(f.den/d));
	}
	frac operator-() const{
		return frac(-num, den);
	}
	frac operator-(const frac& f) const{
		return *this + (-f);
	}
	frac operator*(const frac& f) const{
		return frac(num*f.num, den*f.den);
	}
	frac operator/(const frac& f) const{
		return frac(num*f.den, den*f.num);
	}
	frac operator+=(const frac& f){
		*this = *this + f;
		return *this;
	}
	frac operator-=(const frac& f){
		*this = *this - f;
		return *this;
	}
	frac operator++(int xd){
		*this = *this + 1;
		return *this;
	}
	frac operator--(int xd){
		*this = *this - 1;
		return *this;
	}
	frac operator*=(const frac& f){
		*this = *this * f;
		return *this;
	}
	frac operator/=(const frac& f){
		*this = *this / f;
		return *this;
	}
	bool operator==(const frac& f) const{
		ll d = __gcd(den, f.den);
		return (num*(f.den/d) == (den/d)*f.num);
	}
	bool operator!=(const frac& f) const{
		ll d = __gcd(den, f.den);
		return (num*(f.den/d) != (den/d)*f.num);
	}
	bool operator >(const frac& f) const{
		ll d = __gcd(den, f.den);
		return (num*(f.den/d) > (den/d)*f.num);
	}
	bool operator <(const frac& f) const{
		ll d = __gcd(den, f.den);
		return (num*(f.den/d) < (den/d)*f.num);
	}
	bool operator >=(const frac& f) const{
		ll d = __gcd(den, f.den);
		return (num*(f.den/d) >= (den/d)*f.num);
	}
	bool operator <=(const frac& f) const{
		ll d = __gcd(den, f.den);
		return (num*(f.den/d) <= (den/d)*f.num);
	}
	frac inverso() const{
		return frac(den, num);
	}
	frac fabs() const{
		frac nueva;
		nueva.num = abs(num);
		nueva.den = den;
		return nueva;
	}
	double value() const{
		return (double)num / (double)den;
	}
	string str() const{
		stringstream ss;
		ss << num;
		if(den != 1) ss << "/" << den;
		return ss.str();
	}
};

ostream &operator<<(ostream &os, const frac & f) { 
	return os << f.str();
}

auto sieve(int n){
	vector<bool> is(n+1, true);
	vector<int> primes;
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return is;
}

const int N = 500;
const auto is = sieve(N);

map<tuple<int, int, int>, frac> mem;

frac f(int start, int seq, int n){
	if(n == 0) return 1;
	auto key = make_tuple(start, seq, n);
	if(mem.count(key)) return mem[key];
	frac& ans = mem[key];
	bool isP = (seq & (1 << (n-1)));
	int nxt = (seq & ~(1 << (n-1)));
	int cnt; frac a, b;
	if(start == 1){
		a = f(start+1, nxt, n-1);
		cnt = 1;
	}else if(start == N){
		b = f(start-1, nxt, n-1);
		cnt = 1;
	}else{
		a = f(start+1, nxt, n-1);
		b = f(start-1, nxt, n-1);
		cnt = 2;
	}
	frac c = (a + b) / cnt;
	if(is[start] == isP){
		ans = c * 2/3;
	}else{
		ans = c/3;
	}
	return ans;
}

frac solve(const string s){
	int n = s.size();
	int m = 0;
	for(int i = 0; i < n; ++i){
		if(s[i] == 'P'){
			m |= (1 << (n-1-i));
		}
	}
	frac ans = 0;
	for(int i = 1; i <= N; ++i){
		ans += f(i, m, n) / 500;
	}
	return ans;
}

int main(){
	cout << solve("PPPPNNPPPNPPNPN") << "\n";
	return 0;
}