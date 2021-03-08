#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

__int128 power(__int128 a, __int128 b){
	__int128 ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

map<tuple<lli, int, lli>, int> mem;

int f(lli n, int k, lli prev = 2){
	if(k == 0) return 1;
	if(k == 1) return (n-prev+1) % mod;
	auto key = make_tuple(n, k, prev);
	if(mem.count(key)) return mem[key];
	int ans = 0;
	for(lli i = prev; power(i, k) <= n; ++i){
		lli nxt = n/i;
		if(nxt == 0) break;
		ans += f(nxt, k-1, i);
		if(ans >= mod) ans -= mod;
	}
	return mem[key] = ans;
}

int D(lli n, lli k){
	int ans = 0;
	for(lli i = 0, two_i = 1; i <= k && two_i <= n; ++i, two_i*=2){
		ans += (k+1-i) % mod * f(n, i) % mod;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	cout << D(1e10, 1e10) - 1 << "\n";
	return 0;
}