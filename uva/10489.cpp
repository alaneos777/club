#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int t, n, b, k, ai;
	cin >> t;
	while(t--){
		cin >> n >> b;
		int ans = 0;
		for(int j = 1; j <= b; j++){
			cin >> k;
			int tmp = 1;
			for(int i = 1; i <= k; i++){
				cin >> ai;
				tmp = (tmp * ai) % n;
			}
			ans = (ans + tmp) % n;
		}
		cout << ans << "\n";
	}
	return 0;
}