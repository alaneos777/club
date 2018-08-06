#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, ai;
	cin >> n >> k;
	int g = k;
	for(int i = 0; i < n; ++i){
		cin >> ai;
		ai %= k;
		g = __gcd(g, ai);
	}
	vector<int> ans;
	for(int d = 0; d < k; ++d){
		if(d % g == 0) ans.push_back(d);
	}
	cout << ans.size() << "\n";
	for(int a : ans){
		cout << a << " ";
	}
	cout << "\n";
	return 0;
}