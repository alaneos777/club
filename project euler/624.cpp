#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 9;

const lli inv4 = mod - mod/4;
const lli sqrt5 = 383008016;
const lli a = (1 + sqrt5) * inv4 % mod;
const lli b = (1 - sqrt5 + mod) * inv4 % mod;

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
	lli N = 1e18;
	lli ans = power(a, N-1) * power(1 - power(a, N) + mod, mod-2) % mod;
	ans -= power(b, N-1) * power(1 - power(b, N) + mod, mod-2) % mod;
	ans = ans * power(2 * sqrt5 % mod, mod-2) % mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}