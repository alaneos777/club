#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld pi = acosl(-1);

ld integrate(function<ld(ld)> f, ld a, ld b){
	ld ans = 0;
	int n = 1000;
	ld delta = (b - a) / n;
	for(int i = 1; i <= n; ++i){
		ans += delta * f(a + delta*i);
	}
	return ans;
}

ld C(ld a, ld b){
	return integrate([&](ld t){
		ld num = a*a*a*a + b*b*b*b + (b*b*b*b - a*a*a*a)*cosl(2*t);
		ld den = a*a + b*b + (b*b - a*a)*cosl(2*t);
		return sqrtl(num/den);
	}, 0, 2*pi);
}

int main(){
	ld ans = C(1, 4) + C(3, 4);
	cout << fixed << setprecision(8) << ans << "\n";
	return 0;
}