#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli exp_bin_mod(lli a, lli b, lli n){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % n;
		b >>= 1;
		a = (a * a) % n;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	lli n, k;
	lli m = 10000007;
	while(cin >> n >> k && !(n == 0 && k == 0)){
		lli ans = exp_bin_mod(n - 1, k, m);
		ans = (ans + exp_bin_mod(n - 1, n - 1, m)) % m;
		ans = (2 * ans) % m;
		ans = (ans + exp_bin_mod(n, k, m)) % m;
		ans = (ans + exp_bin_mod(n, n, m)) % m;
		cout << ans << "\n";
	}
	return 0;
}