#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

lli exp_bin_mod(lli x, lli y, lli n){
	lli ans = 1;
	while(y){
		if(y & 1){
			ans = (ans * x) % n;
		}
		y >>= 1;
		x = (x * x) % n;
	}
	return ans;
}

int main(){
	int c;
	lli x, y, n;
	cin >> c;
	for(int i = 1; i <= c; i++){
		cin >> x >> y >> n;
		cout << exp_bin_mod(x, y, n) << "\n";
	}
	cin >> c;
	return 0;
}