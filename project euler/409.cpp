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

const int M = 1e7;
const lli two = power(2, M);

struct poly{
	lli x, y;
	poly(): x(0), y(0){}
	poly(lli x_, lli y_): x(x_), y(y_){
		x %= mod, y %= mod;
		if(x < 0) x += mod;
		if(y < 0) y += mod;
	}
	poly operator+(const poly & p) const{
		return poly(x + p.x, y + p.y);
	}
	poly operator-(const poly & p) const{
		return poly(x - p.x, y - p.y);
	}
	poly operator*(const poly & p) const{
		lli X = x * p.x % mod + y * p.y % mod * (two - 1) % mod;
		lli Y = x * p.y % mod + y * p.x % mod + y * p.y % mod * (two - 2) % mod;
		return poly(X, Y);
	}
	poly operator*(const lli & k) const{
		return poly(x * k, y * k);
	}
};

int main(){
	vector<poly> p = {{two-1, 0}, {0, 1}};
	poly s_odd, s_even, si;
	lli fact = 1;
	for(int i = 1; i <= M; ++i){
		fact = fact * i % mod;
		si = p[i & 1];
		if(i & 1){
			si = si - p[0] * s_odd + p[1] * s_even;
		}else{
			si = si + p[0] * s_even - p[1] * s_odd;
		}
		si = si * power(i & 1 ? i : mod-i, mod - 2);
		if(i & 1){
			s_odd = s_odd + si;
		}else{
			s_even = s_even + si;
		}
	}
	cout << si.y * fact % mod * (two - 1) % mod << "\n";
	return 0;
}