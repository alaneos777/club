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
		return p.cross(*this) < 0 || (p.cross(*this) == 0 && p.dot(*this) < 0);
	}
};

istream& operator>>(istream& is, point& p){
	int x, y;
	is >> x >> y;
	p = point(x, y);
	return is;
}

bool ge(ld a, ld b){return a-b > eps;}
bool le(ld a, ld b){return a-b < -eps;}

struct plane{
	point a, v;
	plane(): a(), v(){}
	plane(const point& a, const point& v): a(a), v(v){}

	point intersect(const plane& p) const{
		ld t = (p.a - a).cross(p.v) / v.cross(p.v);
		return a + v*t;
	}

	bool inside(const point& p) const{
		return v.cross(p - a) >= -eps;
	}

	bool outside(const point& p) const{
		return v.cross(p - a) <= eps;
	}

	bool operator<(const plane& p) const{
		return make_pair(make_pair(v.half(point(1, 0)), ld(0)), v.cross(p.a - a)) < make_pair(make_pair(p.v.half(point(1, 0)), v.cross(p.v)), ld(0));
	}

	bool operator==(const plane& p) const{
		return v.cross(p.v) == 0 && v.dot(p.v) > 0;
	}
};

vector<point> halfPlaneIntersection(vector<plane> planes){
	point p = planes[0].a;
	int n = planes.size();
	random_shuffle(planes.begin(), planes.end());
	for(int i = 0; i < n; ++i){
		if(planes[i].inside(p)) continue;
		ld lo = -inf, hi = inf;
		for(int j = 0; j < i; ++j){
			ld A = planes[j].v.cross(planes[i].v);
			ld B = planes[j].v.cross(planes[j].a - planes[i].a);
			if(ge(A, 0)){
				lo = max(lo, B/A);
			}else if(le(A, 0)){
				hi = min(hi, B/A);
			}else{
				if(ge(B, 0)) return vector<point>();
			}
			if(lo > hi) return vector<point>();
		}
		p = planes[i].a + planes[i].v*lo;
	}
	return vector<point>(1, p);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	int caso = 1;
	while(cin >> n && n){
		vector<point> P(n);
		for(int i = 0; i < n; ++i){
			cin >> P[i];
		}
		reverse(P.begin()+1, P.end());
		vector<plane> planes(n);
		for(int i = 0; i < n; ++i){
			planes[i] = plane(P[i], P[(i+1)%n] - P[i]);
		}
		cout << "Floor #" << caso++ << "\n";
		if(halfPlaneIntersection(planes).empty()){
			cout << "Surveillance is impossible.\n";
		}else{
			cout << "Surveillance is possible.\n";
		}
		cout << "\n";
	}
	return 0;
}