#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n+1), pref(n+1);
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
		pref[i] = pref[i-1] ^ a[i];
	}
	map<int, int> even, odd;
	for(int i = 0; i <= n; ++i){
		if(i & 1) odd[pref[i]]++;
		else even[pref[i]]++;
	}
	lli ans = 0;
	for(auto par : even){
		lli f = par.second;
		ans += f * (f - 1) / 2;
	}
	for(auto par : odd){
		lli f = par.second;
		ans += f * (f - 1) / 2;
	}
	cout << ans << "\n";
	return 0;
}