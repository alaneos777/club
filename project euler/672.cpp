#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 9;
const int k = pow(10, M);
const int L = k-2;
const int mod = 1117117717;

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
	lli n = (power(7, k) - 1) * power(11, mod-2) % mod;
	vector<int> digits = {5, 5, 3, 2, 6, 1, 1, 3, 4, 0};
	lli inv_7 = power(7, mod-2);
	lli ans = (6ll * L * power(7, L) % mod + (n - power(7, L) + 1) * (6ll*L + 7) % mod - 6ll * (L + 1) % mod - n * (n+1) % mod * power(2, mod-2) % mod) % mod;
	if(ans < 0) ans += mod;
	lli rem = (n - digits[0]) * inv_7 % mod;
	lli power_7 = 7;
	for(int i = 1; i <= L; ++i){
		ans = (ans - 3 * power_7 * rem % mod * (rem + 1) % mod + 6 * n * rem % mod) % mod;
		if(ans < 0) ans += mod;
		power_7 = power_7 * 7 % mod;
		rem = (rem - digits[i % 10]) * inv_7 % mod;
		if(rem < 0) rem += mod;
	}
	cout << ans << "\n";
	return 0;
}