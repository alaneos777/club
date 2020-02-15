#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-9;

bool geq(ld a, ld b){return a-b >= -eps;}
bool eq(ld a, ld b){return abs(a-b) <= eps;}
bool ge(ld a, ld b){return a-b > eps;}
bool le(ld a, ld b){return b-a > eps;}

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

int intersectLineSegmentInfo(const point & a, const point & v, const point & c, const point & d){
	point v2 = d - c;
	ld det = v.cross(v2);
	if(eq(det, 0)){
		if(eq((c - a).cross(v), 0)){
			return -1;
		}else{
			return 0;
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a));
	}
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
			if(p != P[i] && p != P[(i+1)%n]){
				lhs.push_back(p);
			}
		}
	}
	return lhs;
}

ld area(const vector<point> & P){
	ld ans = 0;
	for(int i = 0; i < P.size(); ++i){
		ans += P[i].cross(P[(i+1)%P.size()]);
	}
	return ans / 2;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n;
	vector<point> polygon(n);
	for(point & p : polygon){
		cin >> p;
	}
	cin >> q;
	while(q--){
		point a, b;
		cin >> a >> b;
		auto cut = cutPolygon(polygon, a, b - a);
		cout << fixed << setprecision(10) << area(cut) << "\n";
	}
	return 0;
}