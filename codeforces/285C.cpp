#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	sort(a.begin(), a.end());
	lli ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += abs(a[i-1] - i);
	}
	cout << ans << "\n";
	return 0;
}