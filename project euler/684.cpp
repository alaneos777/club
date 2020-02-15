#include <iostream>
using namespace std;
using lli = int64_t;
const lli mod = 1e9+7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli S(lli n){
	lli q = n/9;
	lli ans = 5*(power(10, q)-1)%mod;
	for(lli k = q*9; k <= n; ++k){
		(ans += (k%9+1)*power(10, k/9)%mod) %= mod;
	}
	(ans -= n+1) %=mod;
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	lli f0=0 , f1=1;
	lli sum = 0;
	for(int i = 2; i <= 90; ++i){
		lli fi = f0 + f1;
		(sum += S(fi)) %= mod;
		f0 = f1, f1 = fi;
	}
	cout << sum;
	return 0;
}