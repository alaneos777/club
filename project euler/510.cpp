#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 1e9;

inline lli P1(lli n){
	return n*(n+1)/2;
}

int main(){
	lli ans = 0;
	for(lli m = 1; m*m*m*m <= N; ++m){
		for(lli n = m; n*n*(m+n)*(m+n) <= N; ++n){
			if(__gcd(m, n) != 1) continue;
			lli a = m*(m+n);
			lli b = n*(m+n);
			lli c = m*n;
			ans += (a*a + b*b + c*c) * P1(N / (b*b));
		}
	}
	cout << ans << "\n";
	return 0;
}