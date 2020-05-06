#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli sum1(lli n){
	lli a = 2, b = 3, k = 1;
	lli ans = 0;
	while(!(a <= n && n <= b)){
		ans += k * (b - a + 1);
		a <<= 1;
		b = (b << 1) + 1;
		k++;
	}
	ans += k * (n - a + 1);
	return ans;
}

lli sum2(lli n){
	lli mult = 1, v = 0;
	lli ans = 0;
	while(mult <= n){
		ans += v * (((n - (1ll << v)) >> (v+1)) + 1);
		mult <<= 1;
		v++;
	}
	return ans;
}

int main(){
	lli n = 1e16;
	lli ans = sum1(n+1) - sum2(n+1);
	cout << ans << "\n";
	return 0;
}