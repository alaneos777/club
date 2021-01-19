#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

lli power(lli a, lli b, lli mod){
	lli sum = 1;
	while(b){
		if(b & 1) sum = (__int128)sum * a % mod;
		b >>= 1;
		a = (__int128)a * a % mod;
	}
	return sum;
}

int main(){
	lli n = 1e16;
	n--;
	lli pow_3 = 3;
	ld sum = 0;
	while(pow_3 <= n){
		sum += (ld)power(10, n - pow_3, pow_3) / (ld)pow_3;
		pow_3 *= 3;
	}
	sum -= floorl(sum);
	lli ans = (lli)floorl(sum*1e10);
	cout << ans << "\n";
	return 0;
}