#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 10007;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> a(n);
	for(lli& ai : a){
		cin >> ai;
	}
	sort(a.begin(), a.end());
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		(ans += (a[i]%mod)*(a[n-1-i]%mod)) %= mod;
	}
	cout << ans << "\n";
	return 0;
}