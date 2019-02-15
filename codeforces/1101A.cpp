#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli techo(lli a, lli b){
	return (a + b - 1) / b;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli q, l, r, d;
	cin >> q;
	while(q--){
		cin >> l >> r >> d;
		lli x1 = min(1ll, (l - 1) / d) * d;
		lli x2 = techo(r + 1, d) * d;
		if(x1 == 0) cout << x2 << "\n";
		else if(x2 == 0) cout << x1 << "\n";
		else cout << min(x1, x2) << "\n";
	}
	return 0;
}