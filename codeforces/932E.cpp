#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n; int k;
	cin >> n >> k;
	vector<vector<lli>> stirling(k+1, vector<lli>(k+1));
	stirling[0][0] = 1;
	for(int i = 1; i <= k; ++i){
		for(int j = 1; j <= i; ++j){
			stirling[i][j] = (j * stirling[i-1][j] + stirling[i-1][j-1]) % mod;
		}
	}
	lli ans = 0;
	lli p = n;
	for(int i = 1; i <= k && i <= n; ++i){
		ans += stirling[k][i] * p % mod * powerMod(2, n-i) % mod;
		if(ans >= mod) ans -= mod;
		p = p * (n - i) % mod;
	}
	cout << ans << "\n";
	return 0;
}