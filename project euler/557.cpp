#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli Sqrt(lli n){
	if(n < 0) return -1;
	lli r = sqrtl(n);
	if(r*r == n) return r;
	return -1;
}

int main(){
	lli lim = 1e4;
	lli ans = 0;
	for(lli s = 1; s <= lim; ++s){
		for(lli a = 1; a < s; ++a){
			lli num = a*a, den = s+a;
			lli g = __gcd(num, den);
			num /= g, den /= g;
			for(lli t = 1; den*t < s-a; ++t){
				lli d = den*t;
				lli sum = s-a-d, prod = num*t;
				lli diff = Sqrt(sum*sum - 4*prod);
				if(diff != -1){
					lli b = (sum - diff) / 2;
					lli c = (sum + diff) / 2;
					ans += a+b+c+d;
				}
			}
		}
	}
	cout << ans << "\n";
	return 0;
}