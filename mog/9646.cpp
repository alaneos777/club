#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, x;
	cin >> n >> x;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	int ans = 0;
	int idx = 0;
	while(idx < n){
		int prev = idx;
		while(idx < n-1 && a[idx+1] - a[idx] <= x){
			idx++;
		}
		ans = max(ans, idx-prev+1);
		idx++;
	}
	cout << ans << "\n";
	return 0;
}