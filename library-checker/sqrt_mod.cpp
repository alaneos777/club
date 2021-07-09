#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli sqrtMod(lli a, lli p){
	a %= p;
	if(a < 0) a += p;
	if(a == 0) return 0;
	if(powerMod(a, (p - 1) / 2, p) != 1) return -1;
	if(p % 4 == 3) return powerMod(a, (p + 1) / 4, p);
	lli s = p - 1;
	int r = 0;
	while((s & 1) == 0) ++r, s >>= 1;
	lli n = 2;
	while(powerMod(n, (p - 1) / 2, p) != p - 1) ++n;
	lli x = powerMod(a, (s + 1) / 2, p);
	lli b = powerMod(a, s, p);
	lli g = powerMod(n, s, p);
	while(true){
		lli t = b;
		int m = 0;
		for(; m < r; ++m){
			if(t == 1) break;
			t = t * t % p;
		}
		if(m == 0) return x;
		lli gs = powerMod(g, 1 << (r - m - 1), p);
		g = gs * gs % p;
		x = x * gs % p;
		b = b * g % p;
		r = m;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int y, p;
		cin >> y >> p;
		cout << sqrtMod(y, p) << "\n";
	}
	return 0;
}