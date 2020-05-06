#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

int N(int p, int q, int nines){
	int a = p + q;
	int b = 4 * p * q;
	if((a - 1) * (a - 1) >= b) return 0;
	ld k = log10l(1.0l / (a - sqrtl(b)));
	int l = nines / k * 0.9, r = nines / k * 1.1, n;
	while(l <= r){
		int m = (l + r) / 2;
		if(floor(m * k) >= nines){
			n = m;
			r = m - 1;
		}else{
			l = m + 1;
		}
	}
	return n;
}

const int lim = 2011;

int main(){
	lli ans = 0;
	for(int p = 1; p <= lim; ++p){
		for(int q = p+1; q <= lim-p; ++q){
			ans += N(p, q, lim);
		}
	}
	cout << ans << "\n";
	return 0;
}