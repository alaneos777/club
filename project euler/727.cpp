#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using ld = long double;

struct pt{
	ld x, y;
	pt(): x(0), y(0) {}
	pt(ld x, ld y): x(x), y(y) {}
	pt operator-(const pt & p) const{return pt(x - p.x, y - p.y);}
	pt operator+(const pt & p) const{return pt(x + p.x, y + p.y);}
	pt operator*(const ld & k) const{return pt(x*k, y*k);}
	pt operator/(const ld & k) const{return pt(x/k, y/k);}
	ld len() const{return hypotl(x, y);}
};

ld f(ld ap, ld bp, ld cp){
	ld a = bp+cp;
	ld b = ap+cp;
	ld c = ap+bp;
	ld angB = acosl((a*a + c*c - b*b) / (2*a*c));
	pt B(0, 0);
	pt C(a, 0);
	pt A(c*cosl(angB), c*sinl(angB));
	ld r = 1 / (1 / ap + 1 / bp + 1 / cp + 2 * sqrtl(1 / ap / bp + 1 / ap / cp + 1 / bp / cp));
	ld angT = acosl((a*a + (bp+r)*(bp+r) - (cp+r)*(cp+r)) / (2 * a * (bp+r)));
	pt E((bp+r)*cosl(angT), (bp+r)*sinl(angT));
	pt D = (A*a + B*b + C*c) / (a+b+c);
	return (D - E).len();
}

int main(){
	int n = 100;
	ld ans = 0;
	int den = 0;
	for(int a = 1; a <= n; ++a){
		for(int b = a+1; b <= n; ++b){
			for(int c = b+1; c <= n; ++c){
				if(__gcd(__gcd(a, b), c) == 1){
					ans += f(a, b, c);
					den++;
				}
			}
		}
	}
	cout << fixed << setprecision(8) << ans/den << "\n";
	return 0;
}