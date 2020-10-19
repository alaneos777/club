#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	sort(a.begin(), a.end(), greater<int>());
	int ans = 0;
	for(int i = 0; i < k; ++i){
		ans += a[i];
	}
	cout << ans << "\n";
	return 0;
}