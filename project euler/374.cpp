// https://cs.uwaterloo.ca/journals/JIS/VOL8/Doslic/doslic15.pdf
#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 982451653;

int main(){
	lli N = 1e14;
	int mx = (sqrtl(8*N+1)-1)/2 + 10;
	vector<int> fact(mx+1, 1), inv(mx+1, 1), H(mx+1);
	H[1] = 1;
	for(lli i = 2; i <= mx; ++i){
		fact[i] = i*fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		H[i] = (H[i-1] + inv[i]) % mod;
	}
	lli ans = 1;
	for(lli m = 1; m*(m+1)/2 <= N; ++m){
		ans += (m-1) * fact[m+1] % mod * (H[m] - H[m-min(N-m*(m+1)/2,m-2)-1]) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		if(m*(m+1)/2 + m-1 <= N){
			ans += (m+2) * (m-1) % mod * fact[m] % mod * inv[2] % mod;
			if(ans >= mod) ans -= mod;
		}
		if(m*(m+1)/2 + m <= N){
			ans += m * fact[m+1] % mod;
			if(ans >= mod) ans -= mod;
		}
	}
	cout << ans << "\n";
	return 0;
}