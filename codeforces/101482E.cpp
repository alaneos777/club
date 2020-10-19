#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using ld = long double;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	ld p, s, v;
	cin >> n >> p >> s >> v;
	ld a = n / p / 1e9;
	ld b = powl(log2l(n), sqrtl(2));
	ld d = s/v;
	auto f = [&](ld x){
		return a*powl(b, x) + d + d/x;
	};
	auto fp = [&](ld x){
		return a*powl(b, x)*logl(b) - d / x / x;
	};
	auto fpp = [&](ld x){
		return a*powl(b, x)*logl(b)*logl(b) + 2*d / x / x / x;
	};
	ld c = 1;
	for(int i = 1; i <= 100; ++i){
		c -= fp(c) / fpp(c);
	}
	cout << fixed << setprecision(20) << f(c) << " " << c << "\n";
	return 0;
}