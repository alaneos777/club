#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<lli> a(n);
	for(lli& ai : a){
		cin >> ai;
	}
	partial_sum(a.begin(), a.end(), a.begin());
	while(q--){
		int l, r;
		cin >> l >> r;
		--r;
		lli ans = a[r] - (l ? a[l-1] : 0);
		cout << ans << "\n";
	}
	return 0;
}