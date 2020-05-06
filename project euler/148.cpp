#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int lim = (int)1e9 - 1;
	lli ans = 0;
	for(int i = 0; i <= lim; ++i){
		lli row = 1;
		int n = i;
		while(n){
			int dig = n % 7;
			n /= 7;
			row *= dig + 1;
		}
		ans += row;
	}
	cout << ans << "\n";
}