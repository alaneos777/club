#include <bits/stdc++.h>
#include <thread>
using namespace std;
using ld = long double;

const int N = 32;

int main(){
	ld ans = 0;
	ld ncr = N;
	for(int i = 1; i <= N; ++i){
		ld term = ncr * (1ll << i) / ((1ll << i) - 1);
		if(i & 1) ans += term;
		else ans -= term;
		ncr *= ld(N - i) / (i + 1);
	}
	cout << fixed << setprecision(10) << ans << "\n";
	return 0;
}