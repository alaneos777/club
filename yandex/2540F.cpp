#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
struct ld{
	double x;
	ld(): x(0){}
	ld(double x): x(x){}
	ld(double x, double y): x(x/y){}
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

	ld cross(const point& p) const{return x * p.y - y * p.x;}
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

	bool inside(const point& p) const{
		return v.cross(p - a) >= 0;
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
			if(A > 0){
				lo = max(lo, B/A);
			}else if(A < 0){
				hi = min(hi, B/A);
			}else{
				if(B > 0) return {};
			}
			if(lo > hi) return {};
		}
		p = planes[i].a + planes[i].v*lo;
	}
	return {p};
}

bool can(const vector<point>& P, ld m){
	int n = P.size();
	vector<plane> planes(n);
	for(int i = 0, j = 1; i < n; ++i){
		while((P[(i+1)%n] - P[i]).cross(P[(j+1)%n] - P[j]) > 0) j = (j+1) % n;
		point p1 = P[j] + (P[i] - P[j]) * (m / (m+1));
		point p2 = P[j] + (P[(i+1)%n] - P[j]) * (m / (m+1));
		planes[i] = {p1, p2 - p1};
	}
	return !halfPlaneIntersection(planes).empty();
}

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> P(n);
	for(point& p : P){
		cin >> p;
	}
	ld l = 0, r = 1e8;
	while(l != r){
		ld m = (l + r) / 2;
		if(can(P, m)){
			r = m;
		}else{
			l = m;
		}
	}
	cout << fixed << setprecision(10) << (l+r)/2 << "\n";
	return 0;
}