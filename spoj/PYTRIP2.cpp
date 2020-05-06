#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli cnt(lli l, lli r){
	lli ans = 0;
	for(lli n = 1; n*n <= r; ++n){
		for(lli m = n+1; ; m += 2){
			if(__gcd(m, n) != 1) continue;
			lli a = m*m - n*n;
			lli b = 2*m*n;
			lli c = m*m + n*n;
			if(c > r) break;
			// l <= a*k <= r
			// l <= b*k <= r
			// l <= c*k <= r
			ans += max(0ll, r/c - max({(l+a-1)/a, (l+b-1)/b, (l+c-1)/c}) + 1);
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli l, r;
		cin >> l >> r;
		cout << cnt(l, r) << "\n";
	}
	return 0;
}