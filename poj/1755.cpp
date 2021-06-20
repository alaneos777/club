#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <utility>
#include <cassert>
using namespace std;

const long double eps = 1e-16;

struct ld{
	long double x;
	ld(): x(0){}
	ld(long double x): x(x){}
	ld(long double x, long double y): x(x/y){}
	ld operator+(const ld& f) const{
		return ld(x + f.x);
	}
	ld operator-() const{
		return ld(-x);
	}
	ld operator-(const ld& f) const{
		return *this + (-f);
	}
	ld operator*(const ld& f) const{
		return ld(x * f.x);
	}
	ld operator/(const ld& f) const{
		//assert(f != 0);
		return ld(x / f.x);
	}
	ld operator+=(const ld& f){
		*this = *this + f;
		return *this;
	}
	ld operator-=(const ld& f){
		*this = *this - f;
		return *this;
	}
	ld operator++(int xd){
		*this = *this + 1;
		return *this;
	}
	ld operator--(int xd){
		*this = *this - 1;
		return *this;
	}
	ld operator*=(const ld& f){
		*this = *this * f;
		return *this;
	}
	ld operator/=(const ld& f){
		*this = *this / f;
		return *this;
	}
	bool operator==(const ld& f) const{
		return abs(x - f.x) <= eps;
	}
	bool operator!=(const ld& f) const{
		return abs(x - f.x) > eps;
	}
	bool operator >(const ld& f) const{
		return x - f.x > eps;
	}
	bool operator <(const ld& f) const{
		return f.x - x > eps;
	}
	bool operator >=(const ld& f) const{
		return x - f.x >= -eps;
	}
	bool operator <=(const ld& f) const{
		return f.x - x >= -eps;
	}
};

ostream& operator<<(ostream& os, const ld& f){
	return os << f.x;
}

const ld inf = 1e9;

int sgn(ld x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

struct point{
	ld x, y;
	point(){}
	point(ld x, ld y): x(x), y(y) {}

	point operator+(const point& p) const{return point(x + p.x, y + p.y);}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	point operator*(ld k) const{return point(x * k, y * k);}
	point operator/(ld k) const{return point(x / k, y / k);}

	ld dot(const point& p) const{return x * p.x + y * p.y;}
	ld cross(const point& p) const{return x * p.y - y * p.x;}

	bool half(const point& p) const{
		return p.cross(*this) < 0 || (p.cross(*this) == 0 && p.dot(*this) < 0);
	}
};

ostream& operator<<(ostream& os, const point& p){
	return os << "(" << p.x << ", " << p.y << ")";
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
		ch.push_back(p);
		if(ch.size() >= 2){
			if(ch[ch.size()-2].disjoint(ch[ch.size()-1])) return vector<point>();
			poly.push_back(ch[ch.size()-2].intersect(ch[ch.size()-1]));
		}
	}
	while(ch.size() >= 3 && ch.front().outside(poly.back())) ch.pop_back(), poly.pop_back();
	while(ch.size() >= 3 && ch.back().outside(poly.front())) ch.pop_front(), poly.pop_front();
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
	int test = 1;
	while(cin >> n){
		int cnt = 1;
		vector<ld> a(n), b(n), c(n);
		for(int i = 0; i < n; ++i){
			int u, v, w;
			cin >> u >> v >> w;
			a[i] = ld(1, u);
			b[i] = ld(1, v);
			c[i] = ld(1, w);
		}
		for(int i = 0; i < n; ++i){
			vector<plane> planes;
			bool canWin = true;
			for(int j = 0; j < n; ++j){
				if(i == j) continue;
				// a[i]x + b[i]y + c[i] < a[j]x + b[j]y + c[j]
				// Ax + By + C < 0
				ld A = a[i] - a[j];
				ld B = b[i] - b[j];
				ld C = c[i] - c[j];
				// r(t) = t(B, -A) + initPoint
				if(B == 0){
					if(A == 0){
						// C < 0
						if(C >= 0) canWin = false;
					}else{
						planes.push_back(plane(point(-C/A, 0), point(-B, A)));
					}
				}else{
					planes.push_back(plane(point(0, -C/B), point(-B, A)));
				}
			}
			planes.push_back(plane(point(0, 0), point(0, -1)));
			planes.push_back(plane(point(0, 0), point(1, 0)));
			vector<point> poly = halfPlaneIntersection(planes);
			ld A = area(poly);
			if(canWin){
				canWin = (A > 0);
			}
			if(canWin){
				cout << "Yes" << endl;
			}else{
				cout << "No" << endl;
			}
		}
	}
	return 0;
}