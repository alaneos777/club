#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli cnt(int lim){
	lli ans = 0;
	for(lli n = 1; n*n <= lim; ++n){
		for(lli m = n+1; ; m += 2){
			if(__gcd(m, n) != 1) continue;
			lli c = m*m + n*n;
			if(c > lim) break;
			ans += lim / c;
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int l, r;
		cin >> l >> r;
		cout << cnt(r) - cnt(l-1) << "\n";
	}
	return 0;
}