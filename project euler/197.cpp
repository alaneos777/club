#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld f(ld x){
	return floorl(powl(2, 30.403243784 - x*x)) / 1e9;
}

int main(){
	ld u = -1;
	ld values[2];
	for(int i = 1; i <= 50000; ++i){
		u = f(u);
		values[i&1] = u;
	}
	ld ans = values[0] + values[1];
	cout << fixed << setprecision(9) << ans << "\n";
	return 0;
}