#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	freopen("mosalah.in", "r", stdin);
	int t;
	cin >> t;
	while(t--){
		int n, m, x, y;
		cin >> n >> m >> x >> y;
		int ans = n*(x+y)-m;
		if(ans <= 0){
			cout << "0\n";
		}else if(y == 0){
			cout << "-1\n";
		}else{
			cout << ans << "\n";
		}
	}
	return 0;
}