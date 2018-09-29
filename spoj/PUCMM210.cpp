#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	lli mod = 1e9 + 3;
	while(t--){
		long long int _n;
		cin >> _n;
		lli n = _n;
		lli ans = (n * (n + 1) * (2*n + 1) * (3*n*n + 3*n - 1) / 30 + n * n * (n + 1) * (n + 1) / 2 + n * (n + 1) * (2*n + 1) / 6) / 4;
		cout << (long long int)(ans % mod) << "\n";
	}
	return 0;
}