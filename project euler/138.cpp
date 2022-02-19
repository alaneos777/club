#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli ans = 0;
	lli x = 2, y = 1;
	for(int i = 1; i <= 12; ++i){
		tie(x, y) = make_pair(9*x + 20*y, 4*x + 9*y);
		{
			lli L = y, b;
			if((x + 2) % 5 == 0){
				b = 2 * (x + 2) / 5;
			}else{
				b = 2 * (x - 2) / 5;
			}
			cout << L << " " << b << "\n";
		}
		ans += y;
	}
	cout << ans << "\n";
	return 0;
}