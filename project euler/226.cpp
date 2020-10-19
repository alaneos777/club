#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-18;
const ld pi = acosl(-1);

bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b

ld blanc(ld x){
	if(leq(x, 0) || geq(x, 1)) return 0;
	if(eq(x, 0.5l)) return 0.5l;
	if(geq(x, 0.5l)) return blanc(1 - x);
	return blanc(2*x)/2 + x;
}

ld blanc_area(ld x){
	if(leq(x, 0)) return 0;
	if(geq(x, 1)) return 0.5l;
	if(eq(x, 0.5l)) return 0.25l;
	if(geq(x, 0.5l)) return 0.5l - blanc_area(1 - x);
	return blanc_area(2*x)/4 + x*x/2;
}

ld circ(ld x){
	return 0.5l - sqrtl(x/2 - x*x);
}

ld circ_area(ld x){
	return x/2 - asinl(4*x-1)/32 - (4*x-1)*sqrtl(2*x - 4*x*x)/16 - pi/64;
}

int main(){
	ld l = 0.078, r = 0.079;
	while(abs(l-r) >= eps){
		ld m = (l + r) / 2;
		if(blanc(m) - circ(m) < 0){
			l = m;
		}else{
			r = m;
		}
	}
	ld x0 = l, x1 = 0.5l;
	ld ans = blanc_area(x1) - blanc_area(x0) - (circ_area(x1) - circ_area(x0));
	cout << fixed << setprecision(8) << ans << "\n";
	return 0;
}