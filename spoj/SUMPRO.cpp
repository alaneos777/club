#include <iostream>
#include <cmath>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli sum2(lli n){
	return n * (n + 1) / 2 % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		lli ans = 0;
		int m = sqrt(n);
		for(lli i = 1; i <= n/m; ++i){
			ans = (ans + i * (n / i) % mod) % mod;
		}
		for(lli i = 1; i < m; ++i){
			ans = (ans + (sum2(n / i) - sum2(n / (i + 1))) * i % mod) % mod;
			if(ans < 0) ans += mod;
		}
		cout << ans << "\n";
	}
	return 0;
}