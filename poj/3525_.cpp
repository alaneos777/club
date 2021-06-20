// send using C++
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <utility>
#include <cassert>
using namespace std;

const long double eps = 1e-9;
struct ld{
	long double x;
	ld(): x(0){}
	ld(long double x): x(x){}
	ld(long double x, long double y): x(x/y){}
	ld operator+(const ld& f) const{return ld(x + f.x);}
	ld operator-() const{return ld(-x);}
	ld operator-(const ld& f) const{return *this + (-f);}
	ld operator*(const ld& f) const{return ld(x * f.x);}
	ld operator/(const ld& f) const{return ld(x / f.x);}
	ld operator+=(const ld& f){*this = *this + f; return *this;}
	ld operator-=(const ld& f){*this = *this - f; return *this;}
	ld operator++(int xd){*this = *this + 1; return *this;}
	ld operator--(int xd){*this = *this - 1; return *this;}
	ld operator*=(const ld& f){*this = *this * f; return *this;}
	ld operator/=(const ld& f){*this = *this / f; return *this;}
	bool operator==(const ld& f) const{return abs(x - f.x) <= eps;}
	bool operator!=(const ld& f) const{return abs(x - f.x) > eps;}
	bool operator>(const ld& f) const{return x - f.x > eps;}
	bool operator<(const ld& f) const{return f.x - x > eps;}
	bool operator>=(const ld& f) const{return x - f.x >= -eps;}
	bool operator<=(const ld& f) const{return f.x - x >= -eps;}
};
istream& operator>>(istream& is, ld& f){return is >> f.x;}
ostream& operator<<(ostream& os, const ld& f){return os << f.x;}

const ld inf = 1e18;

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
		ld len = sqrtl((x*x + y*y).x);
		return point(x/len, y/len);
	}

	bool half(const point& p) const{
		return p.cross(*this) < 0 || (p.cross(*this) == 0 && p.dot(*this) < 0);
	}
};

istream& operator>>(istream& is, point& p){
	int x, y;
	is >> x >> y;
	p = point(x, y);
	return is;
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
		return v.cross(p - a) < 0;
	}

	bool operator<(const plane& p) const{
		return make_pair(make_pair(v.half(point(1, 0)), ld(0)), v.cross(p.a - a)) < make_pair(make_pair(p.v.half(point(1, 0)), v.cross(p.v)), ld(0));
	}

	bool operator==(const plane& p) const{
		return v.cross(p.v) == 0 && v.dot(p.v) > 0;
	}

	bool disjoint(const plane& p) const{
		return v.cross(p.v) == 0 && v.dot(p.v) < 0 && (p.a - a).cross(v) != 0;
	}
};

vector<point> halfPlaneIntersection(vector<plane> planes){
	planes.push_back(plane(point(0, -inf), point(1, 0)));
	planes.push_back(plane(point(inf, 0), point(0, 1)));
	planes.push_back(plane(point(0, inf), point(-1, 0)));
	planes.push_back(plane(point(-inf, 0), point(0, -1)));
	sort(planes.begin(), planes.end());
	planes.erase(unique(planes.begin(), planes.end()), planes.end());
	deque<plane> ch;
	deque<point> poly;
	for(int i = 0; i < planes.size(); ++i){
		plane p = planes[i];
		while(ch.size() >= 2 && p.outside(poly.back())) ch.pop_back(), poly.pop_back();
		while(ch.size() >= 2 && p.outside(poly.front())) ch.pop_front(), poly.pop_front();
		if(p.v.half(point(1, 0)) && poly.empty()) return vector<point>();
		ch.push_back(p);
		if(i >= 1) poly.push_back(ch[ch.size()-2].intersect(ch[ch.size()-1]));
	}
	while(ch.size() >= 3 && ch.front().outside(poly.back())) ch.pop_back(), poly.pop_back();
	while(ch.size() >= 3 && ch.back().outside(poly.front())) ch.pop_front(), poly.pop_front();
	poly.push_back(ch.back().intersect(ch.front()));
	return vector<point>(poly.begin(), poly.end());
}

vector<plane> displace(const vector<plane>& planes, ld r){
	vector<plane> ans;
	for(int i = 0; i < planes.size(); ++i){
		plane p = planes[i];
		point w = p.v.perp().unit();
		ans.push_back(plane(p.a + w*r, p.v));
	}
	return ans;
}

ld inradius(const vector<plane>& planes){
	ld l = 0, r = 1e5;
	while(abs((l-r).x) >= eps){
		ld m = (l + r) / 2;
		if(halfPlaneIntersection(displace(planes, m)).empty()) r = m;
		else l = m;
	}
	return (l + r) / 2;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n && n){
		vector<point> P(n);
		for(int i = 0; i < n; ++i){
			cin >> P[i];
		}
		vector<plane> planes(n);
		for(int i = 0; i < n; ++i){
			planes[i] = plane(P[i], P[(i+1)%n] - P[i]);
		}
		cout << fixed << setprecision(9) << inradius(planes) << "\n";
	}
	return 0;
}