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
	lli n, k;
	cin >> t;
	while(t--){
		cin >> n >> k;
		long double f = k * log10(n);
		f -= floor(f);
		f = pow(10, f) * 100;
		lli first = (lli)floor(f);
		lli last = exp_bin_mod(n % 1000, k, 1000);
		cout << first << "..." << setfill('0') << setw(3) << last << "\n";
	}
	return 0;
}