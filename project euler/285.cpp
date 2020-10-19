#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
using ld = long double;

ld area(ld a, ld b, ld r){
	return 0.5l * r*r * (asinl(sqrtl(r*r - b*b)/r) -asinl(a/r)) - 0.5l * b * sqrtl(r*r - b*b) - 0.5l * a * sqrtl(r*r - a*a) + a*b;
}

ld avg(int k){
	ld ans = area(1.0l/k, 1.0l/k, 1+0.5l/k);
	if(k > 1) ans -= area(1.0l/k, 1.0l/k, 1-0.5l/k);
	return ans * k;
}

int main(){
	ld ans = 0;
	for(int k = 1; k <= 1e5; ++k){
		ans += avg(k);
	}
	cout << fixed << setprecision(5) << ans << "\n";
	return 0;
}