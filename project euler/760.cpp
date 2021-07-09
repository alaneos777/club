#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
const lli inv_2 = (mod + 1) / 2;
const lli inv_3 = (mod + 1) / 3;

map<lli, lli> mem;
lli b(lli n){
	if(n == 0 || n == 1) return 0;
	if(mem.count(n)) return mem[n];
	return mem[n] = (2*b(n/2-1) + 2*b(n/2) + 4*b((n-1)/2) + (n/2 % mod) % mod * ((n/2 + 1) % mod) % mod * inv_2 % mod) % mod;
}

lli G(lli n){
	lli ans = (n % mod) * ((n+1) % mod) % mod * ((n+2) % mod) % mod * inv_3 % mod;
	ans -= b(n);
	if(ans < 0) ans += mod;
	ans = ans*2 % mod;
	return ans;
}

int main(){
	cout << G(1e18) << "\n";
	return 0;
}