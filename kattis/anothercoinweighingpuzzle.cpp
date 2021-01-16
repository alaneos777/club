#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 998244353;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<int> muSieve(int n){
	vector<int> mu(n+1, -1);
	mu[0] = 0, mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(mu[i]){
			for(int j = 2*i; j <= n; j += i){
				mu[j] -= mu[i];
			}
		}
	}
	return mu;
}

const int M = 1e6 + 10;
const vector<int> mu = muSieve(M);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, k;
	cin >> m >> k;
	lli ans = 0;
	for(int d = 1; d <= k; ++d){
		lli term = power(2*(k/d) + 1, m) - 1;
		if(term < 0) term += mod;
		if(mu[d] == 1){
			ans += term;
			if(ans >= mod) ans -= mod;
		}else if(mu[d] == -1){
			ans -= term;
			if(ans < 0) ans += mod;
		}
	}
	if(ans >= mod) ans -= mod;
	ans = (ans + 1) % mod;
	cout << ans << "\n";
	return 0;
}