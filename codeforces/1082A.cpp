#include <bits/stdc++.h>
using namespace std;

const int inf = numeric_limits<int>::max();

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n, x, y, d;
		cin >> n >> x >> y >> d;
		if((x - y) % d == 0){
			cout << abs((x - y) / d) << "\n";
		}else{
			int stepsToOne = (x - 1 + d-1) / d;
			int stepsToY = (y - 1) / d;
			int a = ((y - 1) % d == 0 ? stepsToOne + stepsToY : inf);
			int stepsToN = (n - x + d-1) / d;
			stepsToY = (n - y) / d;
			int b = ((n - y) % d == 0 ? stepsToN + stepsToY : inf);
			int ans = min(a, b);
			if(ans == inf){
				cout << "-1\n";
			}else{
				cout << ans << "\n";
			}
		}
	}
	return 0;
}