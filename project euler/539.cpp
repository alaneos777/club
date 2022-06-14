#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 987654321;

map<lli, lli> mem;
lli S(lli n){
	if(n == 0) return 0;
	if(n == 1) return 1;
	if(n == 2) return 3;
	if(n == 3) return 5;
	if(mem.count(n)) return mem[n];
	lli ans = (4*(S(n/4) + S((n-1)/4) + S((n-2)/4) + S((n-3)/4)) + 5 - 2*(n/4 + (n-1)/4)) % mod;
	if(ans < 0) ans += mod;
	return mem[n] = ans;
}

int main(){
	cout << S(1e18) << "\n";
	return 0;
}