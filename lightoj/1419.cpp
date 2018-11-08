#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

lli mod = 1e9 + 7;

lli power(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n;
	lli k;
	vector<lli> phi(1001);
	for(int i = 1; i <= 1000; ++i) phi[i] = i;
	for(int i = 2; i <= 1000; ++i){
		if(phi[i] == i)
			for(int j = i; j <= 1000; j += i)
				phi[j] -= phi[j] / i;
	}
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		cin >> n >> k;
		lli ans = 0;
		for(int d = 1, l = sqrt(n); d <= l; ++d){
			if(n % d > 0) continue;
			int d2 = n / d;
			ans += phi[d] * power(k, d2, mod) % mod;
			if(d != d2)
				ans += phi[d2] * power(k, d, mod) % mod;
			ans %= mod;
		}
		ans *= power(n, mod - 2, mod);
		ans %= mod;
		cout << "Case " << caso << ": " << ans << "\n";
	}
	return 0;
}