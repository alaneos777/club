#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, sum = 0;
	cin >> n;
	vector<lli> a(n);
	for(lli & ai : a){
		cin >> ai;
		sum += ai;
	}
	sort(a.begin(), a.end());
	lli ans = sum;
	for(int i = 1; i < n; ++i){
		for(lli d = 2; d <= a[i]; ++d){
			if(a[i] % d != 0) continue;
			ans = min(ans, sum - a[0] - a[i] + a[0]*d + a[i]/d);
		}
	}
	cout << ans << "\n";
	return 0;
}