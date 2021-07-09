#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int L = 1053779;
	lli ans = 0;
	for(lli n = 1; n <= sqrtl(6*L)/sqrtl(sqrtl(3)); ++n){
		for(lli m = 2*n; m <= n + 6*L/(sqrtl(3)*n); ++m){
			if(__gcd(m, n) == 1){
				lli a = m*m - m*n + n*n;
				lli b = 2*m*n - n*n;
				lli c = m*m - n*n;
				if(b >= c) swap(b, c);
				lli d = __gcd(__gcd(a, b), c);
				a /= d, b /= d, c /= d;
				if(b == c) continue;
				ans += 2*sqrtl(3)*L/(-a+b+c);
			}
		}
	}
	cout << ans << "\n";
	return 0;
}