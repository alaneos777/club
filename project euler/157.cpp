#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli divs(lli n){
	lli ans = 0;
	for(lli d = 1; d*d <= n; ++d){
		if(n % d) continue;
		ans++;
		if(n / d != d) ans++;
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(int n = 1; n <= 9; ++n){
		for(int i = 0; i <= 2*n; ++i){
			for(int j = 0; j <= 2*n; ++j){
				lli x = power(2, i) * power(5, j);
				lli y = power(10, 2*n) / x;
				if(x > y) break;
				lli d = __gcd(power(10, n) + x, power(10, n) + y);
				ans += divs(d);
			}
		}
	}
	cout << ans << "\n";
	return 0;
}