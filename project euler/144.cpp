#include <bits/stdc++.h>
using namespace std;
using ld = long double;

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	point unit() const{
		ld len = sqrtl(x*x + y*y);
		return point(x / len, y / len);
	}
};

int main(){
	point a(0, 10.1);
	point v = (point(1.4, -9.6) - a).unit();
	int cnt = 0;
	while(true){
		ld A = 4*v.x*v.x + v.y*v.y;
		ld B = 8*a.x*v.x + 2*a.y*v.y;
		ld C = 4*a.x*a.x + a.y*a.y - 100;
		ld D = sqrtl(B*B - 4*A*C);
		ld t2 = (-B + D) / (2*A);
		a = a + v*t2;
		point tangent = point(-a.y, 4*a.x).unit();
		v = tangent * (2*v.dot(tangent)) - v;
		if(-0.01 <= a.x && a.x <= 0.01 && a.y > 0){
			cout << cnt << "\n";
			break;
		}
		cnt++;
	}
	return 0;
}