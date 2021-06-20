#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		lli ans = 0;
		while(true){
			lli h = (sqrtl(24*n + 1) - 1) / 6;
			if(h == 0) break;
			ans++;
			n -= (3*h*h + h) / 2;
		}
		cout << ans << "\n";
	}
	return 0;
}