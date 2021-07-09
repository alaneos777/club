#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int n = 12;
	vector<lli> fact(n+1, 1);
	for(lli i = 2; i <= n; ++i){
		fact[i] = fact[i-1] * i;
	}
	lli ans = 0;
	for(int k = 2; 2*k <= n; ++k){
		ans += fact[n] * (k-1) / (2 * fact[k] * fact[k+1] * fact[n-2*k]);
	}
	cout << ans << "\n";
	return 0;
}