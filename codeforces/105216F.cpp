#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, p;
	cin >> n >> p;
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		int ai;
		cin >> ai;
		if(ai <= p){
			ans = max(ans, ai);
		}
	}
	cout << ans << "\n";
	return 0;
}