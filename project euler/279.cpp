#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli L = 1e8;
	lli ans = 0;
	// 120°
	for(lli n = 1; n*n <= L; ++n){
		for(lli m = n+1; 2*m*m + 3*m*n + n*n <= L; ++m){
			if(__gcd(m, n) == 1 && (m - n) % 3 != 0){
				lli a = m*m + m*n + n*n;
				lli b = 2*m*n + n*n;
				lli c = m*m - n*n;
				ans += L / (a+b+c);
			}
		}
	}
	// 60°
	for(lli n = 1; ; ++n){
		bool enter = false;
		for(lli m = 2*n; 2*m*m + m*n - n*n <= 3*L; ++m){
			enter = true;
			if(__gcd(m, n) == 1){
				lli a = m*m - m*n + n*n;
				lli b = 2*m*n - n*n;
				lli c = m*m - n*n;
				lli d = __gcd(__gcd(a, b), c);
				a /= d, b /= d, c /= d;
				ans += L / (a+b+c);
			}
		}
		if(!enter) break;
	}
	// 90°
	for(lli n = 1; ; ++n){
		bool enter = false;
		for(lli m = n+1; 2*m*m + 2*m*n <= L; ++m){
			enter = true;
			if(__gcd(m, n) == 1 && (m - n) % 2 != 0){
				lli a = m*m - n*n;
				lli b = 2*m*n;
				lli c = m*m + n*n;
				ans += L / (a+b+c);
			}
		}
		if(!enter) break;
	}
	cout << ans << "\n";
	return 0;
}