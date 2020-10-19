#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = int64_t;

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
	lli n;
	cin >> n;
	lli ans = (6 * power(2, n) + 7) % mod * power(13, n-1) % mod;
	cout << ans << "\n";
	return 0;
}