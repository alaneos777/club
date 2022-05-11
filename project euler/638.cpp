#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli C(int a, int b, int k){
	auto[n, r] = make_pair(a+b, min(a, b));
	lli num = 1, den = 1;
	if(k == 1){
		for(int i = n, j = 1; j <= r; --i, ++j){
			num = num * i % mod;
			den = den * j % mod;
		}
	}else{
		lli k_num = power(k, n), k_den = k, k_inv = power(k, mod-2);
		for(int i = n, j = 1; j <= r; --i, ++j){
			num = num * (1 - k_num) % mod;
			den = den * (1 - k_den) % mod;
			if(num < 0) num += mod;
			if(den < 0) den += mod;
			k_num = k_num * k_inv % mod;
			k_den = k_den * k % mod;
		}
	}
	return num * power(den, mod-2) % mod;
}

int main(){
	lli ans = 0;
	int ten = 10;
	for(int k = 1; k <= 7; ++k){
		ans += C(ten + k, ten + k, k);
		if(ans >= mod) ans -= mod;
		ten *= 10;
	}
	cout << ans << "\n";
	return 0;
}