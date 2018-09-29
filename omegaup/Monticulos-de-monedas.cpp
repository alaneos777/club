#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1234567890;

lli modPow(lli a, lli b, lli m){
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
	lli n;
	cin >> n;
	lli ans = (modPow(2, n, mod) - (n + 1)) % mod;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}