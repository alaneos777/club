#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

map<lli, int64_t> mem;
int64_t f(lli n){
	if(n == 0) return 1;
	if(mem.count(n)) return mem[n];
	if(n%2 == 1){
		return mem[n] = f((n-1)/2);
	}else{
		return mem[n] = f(n/2) + f(n/2-1);
	}
}

/*map<lli, int64_t> mem2[100];
int64_t g(lli n, int bit = 0){
	if(n == 0) return 1;
	if((n & ((lli(1) << bit) - 1)) != 0) return 0;
	if(mem2[bit].count(n)) return mem2[bit][n];
	lli term = lli(1) << bit;
	int64_t ans = g(n, bit+1);
	if(n-term >= 0) ans += g(n-term, bit+1);
	if(n-2*term >= 0) ans += g(n-2*term, bit+1);
	return mem2[bit][n] = ans;
}*/

int main(){
	lli N = lli(1e13) * lli(1e12);
	cout << f(N) << "\n";
	return 0;
}