#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld pi = acosl(-1);

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x*k, y*k);}
	point operator/(const ld & k) const{return point(x/k, y/k);}
	ld cross(const point & p) const{return x*p.y - y*p.x;}
	ld length() const{return hypotl(x, y);}
};

point intersect(const point & a1, const point & v1, const point & a2, const point & v2){
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, r;
	cin >> n >> r;
	ld theta = 2*pi/n;
	point a(1, 0), b(cosl(theta*(n-1)/2), sinl(theta*(n-1)/2));
	point c(cosl(theta), sinl(theta)), d(cosl(theta*(n+3)/2), sinl(theta*(n+3)/2));
	point e = intersect(a, b-a, c, d-c);
	ld arc = (e.x + (a.x - e.x)/2) * (a.y - e.y) + theta/2 + sin(2*theta)/4 + (c.x + (e.x - c.x)/2) * (e.y - c.y);
	ld area = (pi - n*arc) * r*r;
	cout << fixed << setprecision(14) << area << "\n";
	return 0;
}