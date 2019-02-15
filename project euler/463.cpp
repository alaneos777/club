/*
function f(N){
	if(mem.has(N)) return mem.get(N);
	var ans = 0;
	if(N <= 3){
		if(N == 0) ans = 0;
        else if(N == 1) ans = 1;
        else if(N == 2) ans = 2;
        else if(N == 3) ans = 5;
    }else{
        var n = Math.floor(N/4), r = N%4;
        if(r == 0) ans = 6*f(2*n) - 5*f(n) - 3*f(n-1) - 1;
        else if(r == 1) ans = 2*f(2*n+1) + 4*f(2*n) - 6*f(n) - 2*f(n-1) - 1;
        else if(r == 2) ans = 3*f(2*n+1) + 3*f(2*n) - 6*f(n) - 2*f(n-1) - 1;
        else if(r == 3) ans = 6*f(2*n+1) - 8*f(n) - 1;
    }
	mem.set(N, ans);
	return ans;
}
*/

#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli mod = 1e9;

lli F(lli n){
	lli ans = n % mod;
	for(int i = 1; ; ++i){
		lli cnt = 0;
		lli lo = 1ll << i;
		lli hi = (1ll << (i + 1)) - 1;
		lli period = 2;
		lli ones = 1;
		if(lo > n) break;
		while(lo <= n){
			lli r;
			if(n <= hi){
				r = n - lo + 1;
			}else{
				r = hi - lo + 1;
			}
			cnt += r / period * ones + max(0ll, r % period - ones);
			lo <<= 1;
			hi <<= 1; hi++;
			period <<= 1;
			ones <<= 1;
		}
		ans = (ans + (cnt % mod) * ((1ll << i) % mod) % mod) % mod;
	}
	return ans;
}

int main(){
	cout << F(power(3, 37)) << "\n";
	return 0;
}