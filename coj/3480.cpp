#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1000;
const lli period = 1500;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> f(period), acum(period);
	f[1] = 1;
	for(int i = 2; i < period; ++i){
		f[i] = f[i-1] + f[i-2];
		if(f[i] >= mod) f[i] -= mod;
	}
	for(int i = 1; i < period; ++i){
		acum[i] = acum[i - 1] + f[i];
	}
	int t;
	cin >> t;
	while(t--){
		lli a, b;
		cin >> a >> b;
		lli l = a / period * period;
		lli r = (b + period) / period * period - 1;
		lli n = (r - l + 1) / period;
		a %= period;
		b %= period;
		l %= period;
		r %= period;
		lli leftExcess = (a >= 1 ? acum[a-1] : 0) - (l >= 1 ? acum[l-1] : 0);
		lli rightExcess = (r >= 0 ? acum[r] : 0) - (b >= 0 ? acum[b] : 0);
		lli ans = acum[period-1] * n - leftExcess - rightExcess;
		cout << ans << "\n";
	}
	return 0;
}