#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

map<pair<lli, lli>, lli> mem;

lli f(lli n, lli m){
	if(m < 0 || n < 0) return 0;
	if(m == 0) return n==0;
	if(n > 4*m) return 0;
	if(mem.count({n, m})) return mem[{n, m}];
	return mem[{n, m}] = f(n, m/2) + f(n-m, m/2) + f(n-2*m, m/2);
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int main(){
	lli N = power(10, 25);
	lli acum = 1;
	while(acum <= N) acum *= 2;
	acum /= 2;
	cout << (int64_t)f(N, acum) << "\n";
	return 0;
}