#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int64_t k;
	cin >> k;
	lli n = k;
	int64_t ans = (n*n*n*n - 6*n*n*n + 23*n*n - 18*n + 24) / 24;
	cout << ans << "\n";
	return 0;
}