#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-10;
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

const ld inf = 2e6;

struct point{
	ld x, y;
	point(){}
	point(ld x, ld y): x(x), y(y) {}

	point operator+(const point& p) const{return point(x + p.x, y + p.y);}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	point operator*(ld k) const{return point(x * k, y * k);}

	ld dot(const point& p) const{return x * p.x + y * p.y;}
	ld cross(const point& p) const{return x * p.y - y * p.x;}

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

	bool outside(const point& p) const{ // test if point p is strictly outside
		return v.cross(p - a) < 0;
	}

	bool operator<(const plane& p) const{ // sort by angle
		auto lhs = make_tuple(v.half({1, 0}), ld(0), v.cross(p.a - a));
		auto rhs = make_tuple(p.v.half({1, 0}), v.cross(p.v), ld(0));
		return lhs < rhs;
	}

	bool operator==(const plane& p) const{ // paralell and same directions, not really equal
		return v.cross(p.v) == 0 && v.dot(p.v) > 0;
	}

	bool opposite(const plane& p) const{ // paralell and opposite directions
		return v.cross(p.v) == 0 && v.dot(p.v) < 0; 
	}
};

vector<point> halfPlaneIntersection(vector<plane> planes){
	planes.push_back({{0, -inf}, {1, 0}});
	planes.push_back({{inf, 0}, {0, 1}});
	planes.push_back({{0, inf}, {-1, 0}});
	planes.push_back({{-inf, 0}, {0, -1}});
	sort(planes.begin(), planes.end());
	planes.erase(unique(planes.begin(), planes.end()), planes.end());
	deque<plane> ch;
	deque<point> poly;
	for(const plane& p : planes){
		while(ch.size() >= 2 && p.outside(poly.back())) ch.pop_back(), poly.pop_back();
		while(ch.size() >= 2 && p.outside(poly.front())) ch.pop_front(), poly.pop_front();
		if(p.v.half({1, 0}) && poly.empty()) return {};
		ch.push_back(p);
		if(ch.size() >= 2) poly.push_back(ch[ch.size()-2].intersect(ch[ch.size()-1]));
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

bool isSafe(const vector<point>& P, int k){
	int n = P.size();
	vector<plane> planes(n);
	for(int i = 0; i < n; ++i){
		planes[i] = {P[i], P[(i+k+1) % n] - P[i]};
	}
	return area(halfPlaneIntersection(planes)) > 0;
}

int main(){
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	if(fopen("jungle.in", "r")){
		freopen("jungle.in", "r", stdin);
		freopen("jungle.out", "w", stdout);
	}
	int n;
	cin >> n;
	vector<point> P(n);
	for(point& p : P){
		cin >> p;
	}
	reverse(P.begin() + 1, P.end());
	int l = 0, r = n-2, ans = -1;
	while(l <= r){
		int m = (l + r) / 2;
		if(isSafe(P, m)){
			ans = m;
			l = m+1;
		}else{
			r = m-1;
		}
	}
	cout << ans+1 << "\n";
	return 0;
}