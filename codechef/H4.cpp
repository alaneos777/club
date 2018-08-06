#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

lli exp_bin(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	long long int _n, _m;
	lli n, m;
	cin >> t;
	while(t--){
		cin >> _n >> _m;
		n = _n, m = _m;
		if(m == 1){
			cout << "0\n";
			continue;
		}
		lli ans = 0;
		for(lli k = 1; k < n && k < m; ++k){
			lli l = k + (n - k) / m * m;
			cout << (long long)k << " " << (long long)l << "\n";
			if(k == 1) ans += l % m;
			else ans += (exp_bin(k, l + 1, (k - 1) * m) - k) % ((k - 1) * m) / (k - 1) % m;
		}
		ans %= m;
		cout << (long long int)ans << "\n";
	}
	return 0;
}