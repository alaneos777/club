#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli inv(lli r0, lli r1, lli s0, lli s1){
	return r1 == 0 ? s0 : inv(r1, r0 % r1, s1, s0 - s1 * (r0 / r1));
}

lli mod(lli a, lli b){
	lli r = a % b;
	if(r < 0) r += b;
	return r;
}

lli mult_bin_mod(lli a, lli b, lli n){
	lli ans = 0;
	a %= n, b %= n;
	if(abs(b) > abs(a)) swap(a, b);
	if(b < 0){
		a *= -1, b *= -1;
	}
	while(b){
		if(b & 1) ans = (ans + a) % n;
		b >>= 1;
		a = (a + a) % n;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	lli m = 100000000003;
	lli x1, x2, x3, x4, x5, x6, x7;
	while(cin >> x1 >> x2 >> x3 >> x4 >> x5 >> x6){
		lli d = mod(x2 - x1, m), a, b;
		if(d == 0){
			cout << x1 << "\n";
		}else{
			lli d_inv = inv(d, m, 1, 0);
			a = mult_bin_mod(x3 - x2, d_inv, m);
			b = mult_bin_mod(mult_bin_mod(x2, x2, m) - mult_bin_mod(x1, x3, m), d_inv, m);
			x7 = (mult_bin_mod(a, x6, m) + b) % m;
			if(x7 < 0) x7 += m;
			cout << x7 << "\n";
		}
	}
	return 0;
}