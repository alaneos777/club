#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n; int k;
	cin >> n >> k;
	n %= mod;
	int d = k+1;
	vector<lli> y(d+1);
	for(int i = 1; i <= d; ++i){
		y[i] = (y[i-1] + power(i, k)) % mod;
	}
	if(n <= d){
		cout << y[n] << "\n";
	}else{
		lli ans = 0;
		lli comb = 1;
		for(int j = 0; j <= d; ++j){
			ans += y[j] * comb % mod * power(n-j, mod-2) % mod;
			if(ans >= mod) ans -= mod;
			comb = comb * (d-j) % mod * power(j+1, mod-2) % mod;
			comb = (mod - comb) % mod;
		}
		for(lli den = 1, num = n-1; den <= d; ++den, --num){
			ans = ans * num % mod * power(den, mod-2) % mod;
		}
		ans = ans * n % mod;
		if(d&1) ans = (mod - ans) % mod;
		cout << ans << "\n";
	}
	return 0;
}