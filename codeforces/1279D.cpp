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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> freq(n+1);
	vector<int> cnt(1e6+1);
	for(int i = 1; i <= n; ++i){
		int k;
		cin >> k;
		while(k--){
			int aj;
			cin >> aj;
			freq[i].push_back(aj);
			cnt[aj]++;
		}
	}
	lli ans = 0;
	for(int i = 1; i <= n; ++i){
		lli sum = 0;
		for(int aj : freq[i]){
			sum += cnt[aj];
			if(sum >= mod) sum -= mod;
		}
		sum = sum * power(freq[i].size(), mod-2) % mod;
		ans += sum;
		if(ans >= mod) ans -= mod;
	}
	ans = ans * power(n, mod-3) % mod;
	cout << ans << "\n";
	return 0;
}