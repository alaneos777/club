#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mult(lli a, lli b, lli mod){
	lli ans = 0;
	while(b){
		if(b & 1) ans = (ans + a) % mod;
		b >>= 1;
		a = (a + a) % mod;
	}
	return ans;
}

lli inverse(lli a, lli mod){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si, q;
	while(r1){
		q = r0 / r1;
		ri = r0 - r1*q, r0 = r1, r1 = ri;
		si = s0 - s1*q, s0 = s1, s1 = si;
	}
	if(abs(r0) != 1) return -1;
	if(s0 < 0) s0 += mod;
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli mod;
	int t;
	while(cin >> mod >> t && !(mod == 0 && t == 0)){
		while(t--){
			lli x, y; char op;
			cin >> x >> op >> y;
			lli ans = 0;
			if(op == '+'){
				ans = x + y;
				if(ans >= mod) ans -= mod;
			}else if(op == '-'){
				ans = x - y;
				if(ans < 0) ans += mod;
			}else if(op == '*'){
				ans = mult(x, y, mod);
			}else{
				lli inv = inverse(y, mod);
				if(inv != -1){
					ans = mult(x, inv, mod);
				}else{
					ans = -1;
				}
			}
			cout << ans << "\n";
		}
	}
	return 0;
}