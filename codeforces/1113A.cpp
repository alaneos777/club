#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, v;
	cin >> n >> v;
	lli ans = min(n - 1, v), cnt = min(n - 1, v);
	for(lli i = 2; i <= n; ++i){
		cnt -= 1;
		if(cnt < n-i){
			ans += i;
			cnt += 1;
		}else{
			break;
		}
	}
	cout << ans << "\n";
	return 0;
}