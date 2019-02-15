#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, s;
	cin >> n >> s;
	lli ans = s / n;
	if(s % n > 0) ans++;
	cout << ans << "\n";
	return 0;
}