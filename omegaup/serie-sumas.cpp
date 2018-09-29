#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli exp(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m = 1e7;
	cin >> n;
	lli ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += exp(i, i, m);
		if(ans >= m) ans -= m;
	}
	cout << ans << "\n";
	return 0;
}