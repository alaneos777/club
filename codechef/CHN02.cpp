#include <bits/stdc++.h>
using namespace std;
using ld = double;
const ld inf = 1e18, eps = 1e-9;

struct point{
	ld x, y;
	point(){}
	point(ld x, ld y): x(x), y(y) {}

	point operator+(const point& p) const{
		return point(x + p.x, y + p.y);
	}

	point operator-(const point& p) const{
		return point(x - p.x, y - p.y);
	}

	point operator*(ld k) const{
		return point(x * k, y * k);
	}

	ld dot(const point& p) const{
		return x * p.x + y * p.y;
	}

	ld cross(const point& p) const{
		return x * p.y - y * p.x;
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
		return v.cross(p - a) <= eps;
	}

	bool operator<(const plane& p) const{
		auto lhs = make_tuple(v.half({1, 0}), ld(0), v.cross(p.a - a));
		auto rhs = make_tuple(p.v.half({1, 0}), v.cross(p.v), ld(0));
		return lhs < rhs;
	}

	bool operator==(const plane& p) const{
		return v.cross(p.v) == 0 && v.dot(p.v) > 0;
	}
};

vector<point> halfPlaneIntersection(vector<plane> planes){
	planes.push_back({{-inf, -inf}, {1, 0}});
	planes.push_back({{inf, -inf}, {0, 1}});
	planes.push_back({{inf, inf}, {-1, 0}});
	planes.push_back({{-inf, inf}, {0, -1}});
	sort(planes.begin(), planes.end());
	planes.erase(unique(planes.begin(), planes.end()), planes.end());
	deque<plane> ch;
	deque<point> poly;
	for(const plane& p : planes){
		while(ch.size() >= 2 && p.outside(poly.back())) ch.pop_back(), poly.pop_back();
		while(ch.size() >= 2 && p.outside(poly.front())) ch.pop_front(), poly.pop_front();
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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int cnt;
	cin >> cnt;
	vector<plane> planes;
	while(cnt--){
		int n;
		cin >> n;
		vector<point> P(n);
		for(point& p : P){
			cin >> p;
		}
		for(int i = 0; i < n; ++i){
			planes.push_back({P[i], P[(i+1)%n] - P[i]});
		}
	}
	vector<point> ans = halfPlaneIntersection(planes);
	cout << fixed << setprecision(10) << area(ans) << "\n";
	return 0;
}