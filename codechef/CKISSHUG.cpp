#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli exp_bin_mod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % m;
		b >>= 1;
		a = (a * a) % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t;
	lli m = 1000000007;
	lli n;
	cin >> t;
	while(t--){
		cin >> n;
		lli n1 = (n + 1) >> 1;
		lli n2 = n + 1 - n1;
		lli ans = (exp_bin_mod(2, n1, m) + exp_bin_mod(2, n2, m) - 2) % m;
		cout << ans << "\n";
	}
	return 0;
}