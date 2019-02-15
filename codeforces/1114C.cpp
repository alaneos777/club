#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli potInFactorial(lli n, lli p){
	lli ans = 0, div = n;
	while(div /= p) ans += div;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, b;
	cin >> n >> b;
	map<lli, int> f;
	for(lli d = 2; d*d <= b; ++d){
		int pot = 0;
		while(b % d == 0) b /= d, ++pot;
		if(pot) f[d] = pot;
	}
	if(b > 1) f[b] = 1;
	lli ans = numeric_limits<lli>::max();
	for(auto & par : f){
		lli p = par.first;
		int a = par.second;
		ans = min(ans, potInFactorial(n, p) / a);
	}
	cout << ans << "\n";
	return 0;
}