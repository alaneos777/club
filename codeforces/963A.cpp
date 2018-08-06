#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 9;

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 == -1) s0 *= -1;
	if(s0 < 0) s0 += mod;
	return s0;
}

lli expBin(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	lli n, a, b, k;
	cin >> n >> a >> b >> k;
	vector<lli> signs(k);
	char c;
	for(int i = 0; i < k; ++i){
		cin >> c;
		if(c == '+') signs[i] = 1;
		else signs[i] = -1;
	}
	lli r = b * inv(a, mod) % mod;
	lli ans = 0;
	lli pot = 1;
	lli r_n1 = expBin(r, n + 1, mod);
	for(int j = 0; j < k ; ++j){
		ans += signs[j] * pot;
		pot = pot * r % mod;
	}
	ans = ans % mod * expBin(a, n, mod) % mod;
	lli rk = expBin(r, k, mod);
	if(rk == 1){
		ans = ans * ((n + 1) / k) % mod;
	}else{
		ans = ans * (expBin(r, n + 1, mod) - 1) % mod * inv(rk - 1, mod) % mod;
	}
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}