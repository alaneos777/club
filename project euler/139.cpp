#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli P = 1e8;
	function<lli(lli, lli, lli)> f = [&](lli a, lli b, lli c){
		lli ans = 0;
		if(a+b+c <= P){
			lli diff = abs(a-b);
			if(c % diff == 0){
				ans += P / (a+b+c);
			}
			ans += f(a - 2*b + 2*c, 2*a - b + 2*c, 2*a - 2*b + 3*c);
			ans += f(-a + 2*b + 2*c, -2*a + b + 2*c, -2*a + 2*b + 3*c);
			ans += f(a + 2*b + 2*c, 2*a + b + 2*c, 2*a + 2*b + 3*c);
		}
		return ans;
	};
	lli ans = f(3, 4, 5);
	cout << ans << "\n";
	return 0;
}