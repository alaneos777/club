#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli T(lli n){
	lli ans = 0;
	lli lo_y = ceill(-sqrtl(4.0l*n/163.0l));
	lli hi_y = floorl(sqrtl(4.0l*n/163.0l));
	for(lli y = lo_y; y <= hi_y; ++y){
		lli lo = ceill((-y - sqrtl(4*n - 163*y*y)) / 2.0l);
		lli hi = floorl((-y + sqrtl(4*n - 163*y*y)) / 2.0l);
		ans += hi-lo+1;
	}
	return ans - 1;
}

int main(){
	cout << T(1e16) << "\n";
	return 0;
}