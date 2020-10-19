#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = int64_t;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	ld p;
	cin >> n >> p;
	ld ans = (1 + powl(1 - 2*p, n)) / 2;
	cout << fixed << setprecision(9) << ans << "\n";
	return 0;
}