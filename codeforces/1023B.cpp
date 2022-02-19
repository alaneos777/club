#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, k;
	cin >> n >> k;
	cout << max(min(n-1, (k-1)/2) - max(k-n, 1ll) + 1, 0ll) << "\n";
	return 0;
}