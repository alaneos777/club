// https://math.stackexchange.com/questions/1148380/when-does-ax2y2z2-bxy-yz-xz-have-nontrivial-integer-solutions?noredirect=1&lq=1
#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int N = 1e9;
	lli ans = 0;
	for(lli t = 1; t*t <= 2*N; ++t){
		if(t%19 == 0) continue;
		for(lli u = 1; u*u <= N && 4*t*u <= N; ++u){
			if(__gcd(t, u) == 1 && (t-u)%2 != 0){
				lli x = 3*t*t - 34*t*u + 95*u*u;
				lli y = 5*t*t - 34*t*u + 57*u*u;
				lli z = 4*t*u;
				if(0 < x && x <= N && 0 < y && y <= N && 0 < z && z <= N){
					//cout << x << " " << y << " " << z << "\n";
					ans += x+y+z;
				}
			}
		}
	}
	cout << ans << "\n";
	return 0;
}