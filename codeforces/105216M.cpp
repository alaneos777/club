#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

const ld pi = acosl(-1);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int l, r;
		cin >> l >> r;
        auto f = [&](ld ang) -> ld {
            ld h = l*cosl(ang);
            ld R = r + l*sinl(ang);
            return pi/3*h*(R*R + R*r + r*r);
        };
        ld max_vol = 0, ans = 0;
		ld a = ld(r)/ld(l);
		ld P = -(1.0l*a*a + 2)/3;
		ld Q = -(2.0l*a*a*a + 15.0l*a)/27;
		ld D = (Q/2)*(Q/2) + (P/3)*(P/3)*(P/3);
		if(D < 0){
			ld theta = acosl(-Q/2 * sqrt(-27/P/P/P)) / 3;
			ld x1 = 2 * sqrtl(-P/3) * cosl(theta) - 2*a/3;
			ld x2 = 2 * sqrtl(-P/3) * cosl(theta + 2 * pi / 3) - 2*a/3;
			ld x3 = 2 * sqrtl(-P/3) * cosl(theta + 4 * pi / 3) - 2*a/3;
            for(ld x : {x1, x2, x3}){
                if(-1 <= x && x <= 1){
                    ld ang = asinl(x);
                    ld curr_vol = f(ang);
                    if(curr_vol > max_vol){
                        max_vol = curr_vol;
                        ans = ang + pi/2;
                    }
                }
            }
		}else{
			ld u = cbrtl(-Q/2 + sqrtl(D));
			ld v = cbrtl(-Q/2 - sqrtl(D));
			ld x = u + v - 2*a/3;
            if(-1 <= x && x <= 1){
                ld ang = asinl(x);
                ld curr_vol = f(ang);
                if(curr_vol > max_vol){
                    max_vol = curr_vol;
                    ans = ang + pi/2;
                }
            }
		}
        cout << fixed << setprecision(10) << ans << "\n";
	}
	return 0;
}