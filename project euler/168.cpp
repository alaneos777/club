#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e5;

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
	// n = 10a + b
	// n has d digits
	// a has d-1 digits
	// 1 <= b <= 9
	// right_rotation(n) = b*10^(d-1) + a
	// right_rotation(n) = kn , 1<=k<=9
	// a = b*(10^(d-1) - k)/(10k - 1)
	// n = b(10^d - 1) / (10k - 1)
	lli ans = 0;
	for(int d = 2; d <= 100; ++d){
		for(int k = 1; k <= 9; ++k){
			for(int b = k; b <= 9; ++b){
				int den = 10*k - 1;
				lli MOD = mod * den;
				lli x = b * (power(10, d, MOD) - 1) % MOD;
				if(x < 0) x += MOD;
				if(x % den == 0){
					lli n = x / den;
					ans = (ans + n) % mod;
				}
			}
		}
	}
	cout << ans << "\n";
	return 0;
}