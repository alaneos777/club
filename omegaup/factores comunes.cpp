#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli gcd(lli a, lli b){
	lli r;
	while(b){
		r = a % b, a = b, b = r;
	}
	return a;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	lli a, b;
	cin >> a >> b;
	lli d = gcd(a, b);
	int ans = 1, pot = 0;
	while((d & 1) == 0) d >>= 1, ++pot;
	ans *= pot + 1;
	for(lli p = 3; p <= sqrt(d); p += 2){
		pot = 0;
		while(d % p == 0) d /= p, ++pot;
		ans *= pot + 1;
	}
	if(d > 1) ans *= 2;
	cout << ans;
	return 0;
}