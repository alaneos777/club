#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli a = 0, b = 1;
	lli ans = 1;
	for(int n = 1; n <= 30; ++n){
		ans += b;
		lli c = a + b;
		a = b, b = c;
	}
	cout << ans << "\n";
	return 0;
}