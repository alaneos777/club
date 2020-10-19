#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int M = 1e6;

int main(){
	vector<ld> logfact(M+1);
	for(int i = 2; i <= M; ++i){
		logfact[i] = logfact[i-1] + logl(i);
	}
	int n = 1e6, k = 2e4;
	ld ans = 0;
	for(int i = 0; i <= k/2; ++i){
		ans += expl(logfact[n] + logfact[k] - logfact[i + n-k] - logfact[k - 2*i] - logfact[i] - i*logl(2) - k*logl(n));
	}
	ans = 1 - ans;
	cout << fixed << setprecision(10) << ans << "\n";
	return 0;
}