#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <utility>
#include <cassert>
using namespace std;
typedef double ld;
const ld inf = 1e18, eps = 1e-8;

bool ge(ld a, ld b){return a-b > eps;}
bool le(ld a, ld b){return a-b < -eps;}
bool eq(ld a, ld b){return abs(a-b) < eps;}
bool geq(ld a, ld b){return a-b>=-eps;}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

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
	ld len() const{return sqrt(x*x + y*y);}
	point unit() const{
		ld len = sqrt(x*x + y*y);
		return point(x/len, y/len);
	}

	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool operator==(const point& p) const{return eq(x, p.x) && eq(y, p.y);}
};

istream& operator>>(istream& is, point& p){
	return is >> p.x >> p.y;
}

ostream& operator<<(ostream& os, const point& p){
	return os << p.x << " " << p.y;
}

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

int intersectLineSegmentInfo(const point & a, const point & v, const point & c, const point & d){
	//line a+tv, segment cd
	point v2 = d - c;
	ld det = v.cross(v2);
	if(eq(det, 0)){
		if(eq((c - a).cross(v), 0)){
			return -1; //infinity points
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a)); //1: single point, 0: no point
	}
}

struct plane{
	point a, v;
	plane(): a(), v(){}
	plane(const point& a, const point& v): a(a), v(v){}

	point intersect(const plane& p) const{
		ld t = (p.a - a).cross(p.v) / v.cross(p.v);
		return a + v*t;
	}
};

vector<plane> displace(const vector<plane>& planes, ld r){
	vector<plane> ans;
	for(int i = 0; i < planes.size(); ++i){
		plane p = planes[i];
		point w = p.v.perp().unit();
		ans.push_back(plane(p.a + w*r, p.v));
	}
	return ans;
}

vector<point> cutPolygon(const vector<point> & P, const point & a, const point & v){
	int n = P.size();
	vector<point> lhs;
	for(int i = 0; i < n; ++i){
		if(geq(v.cross(P[i] - a), 0)){
			lhs.push_back(P[i]);
		}
		if(intersectLineSegmentInfo(a, v, P[i], P[(i+1)%n]) == 1){
			point p = intersectLines(a, v, P[i], P[(i+1)%n] - P[i]);
			if(!(p == P[i]) && !(p == P[(i+1)%n])){
				lhs.push_back(p);
			}
		}
	}
	return lhs;
}

pair<point, point> farthestPoints(vector<point> P){
	P.erase(unique(P.begin(), P.end()), P.end());
	int n = P.size();
	if(n == 1) return make_pair(P[0], P[0]);
	if(n == 2) return make_pair(P[0], P[1]);
	int i = 0, j = 1;
	ld ans = -1;
	pair<point, point> res;
	while(i < n){
		while(ge((P[(i+1)%n] - P[i]).cross(P[(j+1)%n] - P[j]), 0)) j = (j + 1) % n;
		ld d = (P[i] - P[j]).len();
		if(ge(d, ans)){
			ans = d;
			res = make_pair(P[i], P[j]);
		}
		i++;
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	ld r;
	while(cin >> n >> r){
		vector<point> P(n);
		for(int i = 0; i < n; ++i){
			cin >> P[i];
		}
		reverse(P.begin()+1, P.end());
		vector<plane> planes(n);
		for(int i = 0; i < n; ++i){
			planes[i] = plane(P[i], P[(i+1)%n] - P[i]);
		}
		planes = displace(planes, r);
		for(int i = 0; i < n; ++i){
			P = cutPolygon(P, planes[i].a, planes[i].v);
		}
		pair<point, point> ans = farthestPoints(P);
		if(ans.second < ans.first) swap(ans.first, ans.second);
		cout << fixed << setprecision(4) << ans.first << " " << ans.second << "\n";
	}
	return 0;
}