#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n;
	lli a, r;
	cin >> t;
	while(t--){
		cin >> n >> a >> r;
		lli ans = 0, a_pw = a;
		for(int i = 1; i <= n; ++i){
			ans += a_pw * powerMod(i, r) % mod;
			if(ans >= mod) ans -= mod;
			a_pw = a_pw * a % mod;
		}
		cout << ans << "\n";
	}
	return 0;
}