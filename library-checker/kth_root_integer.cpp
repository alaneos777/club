#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli root(lli a, int k){
	lli r = powl(a, 1.0l/k);
	lli ans = r;
	for(lli x = max(lli(0), r-1); x <= r+1; ++x){
		if(power(x, k) <= a) ans = x;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		uint64_t a; int k;
		cin >> a >> k;
		cout << (uint64_t)root(a, k) << "\n";
	}
	return 0;
}