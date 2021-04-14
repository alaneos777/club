#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n, m; int q;
	cin >> n >> m >> q;
	lli d = __gcd(m, n);
	lli sz_n = n/d, sz_m = m/d;
	while(q--){
		int sx, ex;
		lli sy, ey;
		cin >> sx >> sy >> ex >> ey;
		--sy, --ey;
		lli c_s, c_e;
		if(sx == 1){
			c_s = sy / sz_n;
		}else{
			c_s = sy / sz_m;
		}
		if(ex == 1){
			c_e = ey / sz_n;
		}else{
			c_e = ey / sz_m;
		}
		if(c_s == c_e){
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}