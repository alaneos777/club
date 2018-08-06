#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

lli inv(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

lli elevar(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

int main(){
	lli m = 1000000007;
	lli n, k;
	cin >> n >> k;
	vector<lli> suma(k + 2);
	for(lli i = 1; i <= k + 1; i++){
		suma[i] = (suma[i - 1] + elevar(i, k, m)) % m;
	}
	if(n <= k + 1){
		cout << suma[n];
	}else{
		lli ans = 0;
		int alternar = (k & 1 ? 1 : -1);
		lli num = 1, den = 1;
		for(lli i = 1; i <= k + 1; i++){
			num = (num * (n - i)) % m, den = (den * i) % m;
		}
		for(lli i = 0; i <= k + 1; i++){
			ans = (ans + alternar * ((suma[i] * ((num * inv(den, m)) % m)) % m)) % m;
			if(i < k + 1) num = (num * (((n - i) * inv(n - i - 1, m)) % m)) % m, den = (den * (((i + 1) * inv(k + 1 - i, m)) % m)) % m;
			alternar *= -1;
		}
		if(ans < 0) ans += m;
		cout << ans;
	}
	cout << "\n";
	return 0;
}