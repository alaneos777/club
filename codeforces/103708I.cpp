#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int n;
	cin >> n;
	int m = n;
	int ans = 0;
	while(m){
		int d = m%10;
		m /= 10;
		if(d > 0 && n%d == 0) ans++;
	}
	cout << ans << "\n";
	return 0;
}