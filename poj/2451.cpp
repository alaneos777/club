#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <utility>
using namespace std;
typedef long double ld;
const ld inf = 1e18, eps = 1e-9;

struct point{
	ld x, y;
	point(){}
	point(ld x, ld y): x(x), y(y) {}

	point operator+(const point& p) const{return point(x + p.x, y + p.y);}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	point operator*(ld k) const{return point(x * k, y * k);}

	ld dot(const point& p) const{return x * p.x + y * p.y;}
	ld cross(const point& p) const{return x * p.y - y * p.x;}

	point perp() const{return point(-y, x);}
	point unit() const{
		ld len = sqrtl(x*x + y*y);
		return point(x/len, y/len);
	}

	bool half(const point& p) const{
		return p.cross(*this) < -eps || (abs(p.cross(*this)) < eps && p.dot(*this) < -eps);
	}
};

istream& operator>>(istream& is, point& p){
	return is >> p.x >> p.y;
}

struct plane{
	point a, v;
	plane(): a(), v(){}
	plane(const point& a, const point& v): a(a), v(v){}

	point intersect(const plane& p) const{
		ld t = (p.a - a).cross(p.v) / v.cross(p.v);
		return a + v*t;
	}

	bool outside(const point& p) const{
		return v.cross(p - a) <= eps;
	}

	bool operator<(const plane& p) const{
		return make_pair(make_pair(v.half(point(1, 0)), ld(0)), v.cross(p.a - a)) < make_pair(make_pair(p.v.half(point(1, 0)), v.cross(p.v)), ld(0));
	}

	bool operator==(const plane& p) const{
		return abs(v.cross(p.v)) < eps && v.dot(p.v) > eps;
	}
};

vector<point> halfPlaneIntersection(vector<plane> planes){
	planes.push_back(plane(point(-inf, -inf), point(1, 0)));
	planes.push_back(plane(point(inf, -inf), point(0, 1)));
	planes.push_back(plane(point(inf, inf), point(-1, 0)));
	planes.push_back(plane(point(-inf, inf), point(0, -1)));
	sort(planes.begin(), planes.end());
	planes.erase(unique(planes.begin(), planes.end()), planes.end());
	deque<plane> ch;
	deque<point> poly;
	for(int i = 0; i < planes.size(); ++i){
		plane p = planes[i];
		while(ch.size() >= 2 && p.outside(poly.back())) ch.pop_back(), poly.pop_back();
		while(ch.size() >= 2 && p.outside(poly.front())) ch.pop_front(), poly.pop_front();
		ch.push_back(p);
		if(ch.size() >= 2) poly.push_back(ch[ch.size()-2].intersect(ch[ch.size()-1]));
	}
	while(ch.size() >= 3 && ch.front().outside(poly.back())) ch.pop_back(), poly.pop_back();
	while(ch.size() >= 3 && ch.back().outside(poly.front())) ch.pop_front(), poly.pop_front();
	if(ch.size() <= 2) return vector<point>();
	poly.push_back(ch.back().intersect(ch.front()));
	return vector<point>(poly.begin(), poly.end());
}

ld area(const vector<point>& P){
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; ++i){
		ans += P[i].cross(P[(i+1)%n]);
	}
	return ans/2;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<plane> planes(n);
	for(int i = 0; i < n; ++i){
		point a, b;
		cin >> a >> b;
		planes[i] = plane(a, b - a);
	}
	planes.push_back(plane(point(0, 0), point(1, 0)));
	planes.push_back(plane(point(10000, 0), point(0, 1)));
	planes.push_back(plane(point(10000, 10000), point(-1, 0)));
	planes.push_back(plane(point(0, 10000), point(0, -1)));
	cout << fixed << setprecision(1) << area(halfPlaneIntersection(planes)) << "\n";
	return 0;
}