#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	int ans = 0;
	while(n--){
		int x, y;
		cin >> x >> y;
		ans = max(ans, x + y);
	}
	cout << ans << "\n";
	return 0;
}