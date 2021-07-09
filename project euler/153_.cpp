#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli g(lli n){
	return n*(n+1)/2;
}

lli F(lli n){
	lli ans = 0;
	lli i = 1;
	while(i <= n){
		lli ni = n/i, u = n/ni;
		ans += ni * (g(u) - g(i-1));
		i = u+1;
	}
	return ans;
}

int main(){
	lli N = 1e8;
	lli ans = F(N) + 2*F(N/2);
	function<void(int, int)> gen = [&](int x, int y){
		if(x*x + y*y > N) return;
		ans += 2*(x+y)*F(N / (x*x + y*y));
		gen(2*x - y, x);
		gen(2*x + y, x);
		gen(x + 2*y, y);
	};
	gen(2, 1);
	gen(3, 1);
	cout << ans << "\n";
	return 0;
}