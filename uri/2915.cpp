#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}
	a[n] = 1 << 30;
	int ans = 0;
	for(int i = 0; i < n; ++i){
		if(a[i] < a[i+1]) ans++;
	}
	cout << ans << "\n";
	return 0;
}