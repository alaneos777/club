#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9;

int main(){
	const lli N = 1e16;
	lli ans = 0;

	for(lli a = 1; a*a*a*a <= 2*N; a += 2){
		for(lli b = 1; b < a; b += 2){
			lli x = (a*a*a*a - b*b*b*b) / 8;
			lli y = a*b;
			lli z = (a*a*a*a + b*b*b*b) / 2;
			if(!(x <= N && y <= N && z <= N)) break;
			if(__gcd(a, b) != 1) continue;
			assert(z <= N);
			ans = (ans + x+y+z) % mod;
		}
	}

	for(lli a = 1; 4*a*a*a*a <= N; a += 2){
		for(lli b = 1; ; b++){
			lli x = abs(a*a*a*a - 4*b*b*b*b);
			lli y = 4*a*b;
			lli z = 4*a*a*a*a + 16*b*b*b*b;
			if(!(x <= N && y <= N && z <= N)) break;
			if(__gcd(a, b) != 1) continue;
			ans = (ans + x+y+z) % mod;
		}
	}

	cout << ans << "\n";
	return 0;
}