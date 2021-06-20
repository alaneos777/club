#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
	}
	sort(a.begin(), a.end());
	lli ans = 0;
	for(int i = 0; i < n-1; ++i){
		for(int j = i+1; j < n; ++j){
			int start = lower_bound(a.begin(), a.end(), max(a[i]-a[j]+1, a[j]-a[i]+1)) - a.begin();
			int end = upper_bound(a.begin(), a.end(), a[i]+a[j]-1)-1 - a.begin();
			int cnt = end - start + 1;
			if(start <= i && i <= end) cnt--;
			if(start <= j && j <= end) cnt--;
			ans += cnt;
		}
	}
	assert(ans % 3 == 0);
	cout << ans/3 << "\n";
	return 0;
}