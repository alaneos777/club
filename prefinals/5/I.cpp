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
	int t;
	cin >> t;
	while(t--){
		lli n, m, ans;
		cin >> n >> m;
		if(m == 2){
			ans = 2;
		}else if(m == 3){
			ans = 6 * (power(2, n) - 2) % mod;
			if(ans < 0) ans += mod;
		}else if(m == 4){
			ans = (power(3, n) - 3*power(2, n) + power(2, n-1) + 2) % mod * 24 % mod;
			if(ans < 0) ans += mod;
		}else if(m == 5){
			ans = (-120 + 360*power(2, n)%mod - 360*power(3, n)%mod + 120*power(4, n)%mod) % mod;
			if(ans < 0) ans += mod;
		}else{
			ans = (1440 - 2880*power(2, n)%mod + 3600*power(3, n)%mod - 2520*power(4, n)%mod + 720*power(5, n)%mod) % mod;
			if(ans < 0) ans += mod;	
		}
		cout << ans << "\n";
	}
	return 0;
}