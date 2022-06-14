#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int n;
	cin >> n;
	int m = n/2, ans = 0;
	if(m&1) ans = (m*m-1)/4;
	else ans = m*m/4;
	cout << ans << "\n";
	return 0;
}