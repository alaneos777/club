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
	lli t;
	cin >> t;
	while(t--){
		lli a, b;
		cin >> a >> b;
		cout << exp_bin_mod(a % 10, b, 10) << "\n";
	}
	return 0;
}