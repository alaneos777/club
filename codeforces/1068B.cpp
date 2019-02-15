#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli b;
	cin >> b;
	lli ans = 1;
	for(lli d = 2; d*d <= b; ++d){
		lli pot = 0;
		while(b % d == 0){
			b /= d;
			pot++;
		}
		ans *= pot + 1;
	}
	if(b > 1) ans *= 2;
	cout << ans << "\n";
	return 0;
}