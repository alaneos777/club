#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	while(cin >> n && n != 0){
		lli ans = (lli)sqrtl(n);
		ans += (lli)sqrtl(n / 2.0);
		cout << (n - ans) << "\n";
	}
	return 0;
}