#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
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
	int t;
	cin >> t;
	while(t--){
		int n, k;
		cin >> n >> k;
		vector<int> P(k+1), Q(k+1);
		P[0] = 1;
		for(int i = 0; i < k; ++i){
			P[i+1] = (lli)P[i] * (i+n) % mod * power(i+1, mod-2) % mod;
		}
		Q[0] = 1;
		for(int i = 1; i*(3*i+1)/2 <= k; ++i){
			int& pos = Q[i*(3*i+1)/2];
			if(i & 1) pos -= 1;
			else pos += 1;
		}
		for(int i = 1; i*(3*i-1)/2 <= k; ++i){
			int& pos = Q[i*(3*i-1)/2];
			if(i & 1) pos -= 1;
			else pos += 1;
		}
		for(int& qi : Q){
			qi %= mod;
			if(qi < 0) qi += mod;
		}
		lli ans = 0;
		for(int i = 0; i <= k; ++i){
			ans += (lli)P[i] * Q[k-i] % mod;
			if(ans >= mod) ans -= mod;
		}
		cout << ans << "\n";
	}
	return 0;
}