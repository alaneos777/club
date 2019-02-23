#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m, k;
	cin >> n >> m >> k;
	vector<lli> a(n);
	for(lli & ai : a) cin >> ai;
	sort(a.begin(), a.end(), greater<int>());
	lli cycles = m / (k + 1);
	lli rem = m % (k + 1);
	lli ans = (a[0]*k + a[1]) * cycles + a[0]*rem;
	cout << ans << "\n";
	return 0;
}