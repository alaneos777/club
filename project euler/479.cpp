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
	int n = 1e6;
	lli ans = 0;
	for(lli k = 1; k <= n; ++k){
		lli add = (1 - k*k) % mod;
		if(add < 0) add += mod;
		(ans += (add - power(add, n+1)) * power(k, mod - 3) % mod) %= mod;
		if(ans < 0) ans += mod;
	}
	cout << ans << "\n";
	return 0;
}