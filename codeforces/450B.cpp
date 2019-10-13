#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9+7;

lli modula(lli n){
	lli ans = n % mod;
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	lli x, y, n;
	cin >> x >> y >> n;
	n %= 6;
	if(n == 0) cout << modula(x - y);
	if(n == 1) cout << modula(x);
	if(n == 2) cout << modula(y);
	if(n == 3) cout << modula(y - x);
	if(n == 4) cout << modula(-x);
	if(n == 5) cout << modula(-y);
	cout << "\n";
	return 0;
}