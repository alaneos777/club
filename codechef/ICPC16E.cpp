#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using LLI = __int128_t;
const lli mod = 1e9 + 7;
const lli inv_4 = (mod + 1) / 4;

lli power(lli a, LLI b){
	b %= mod-1;
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
		lli n, c;
		cin >> n >> c;
		if(n & 1){
			lli ans = (power(c, (LLI)5*n*n) + 2*power(c, ((LLI)5*n*n - 1)/4 + 1) + power(c, ((LLI)5*n*n - 1)/2 + 1)) % mod * inv_4 % mod;
			cout << ans << "\n";
		}else{
			lli ans = (power(c, (LLI)5*n*n) + 2*power(c, (LLI)5*n*n/4) + power(c, (LLI)5*n*n/2)) % mod * inv_4 % mod;
			cout << ans << "\n";
		}
	}
	return 0;
}