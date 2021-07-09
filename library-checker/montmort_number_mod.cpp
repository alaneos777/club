#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	lli ans = 1;
	for(int i = 1; i <= n; ++i){
		ans = ans * i % m;
		if(i&1) ans--;
		else ans++;
		if(ans >= m) ans -= m;
		if(ans < 0) ans += m;
		cout << ans << " ";
	}
	cout << "\n";
	return 0;
}