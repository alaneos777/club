#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

lli power(lli a, lli b, lli m){
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
	int64_t n, k, m;
	cin >> n >> k >> m;
	lli ans = 2*power(k, (2*n-2 - 3*((n-1)/3)) * ((n+2)/3) / 2 + (n%3==1), 6*m) + power(k, n*(n+1)/2, 6*m) + 3*power(k, ((n+1)/2)*(n/2+1), 6*m);
	ans %= 6*m;
	ans /= 6;
	cout << int64_t(ans) << "\n";
	return 0;
}