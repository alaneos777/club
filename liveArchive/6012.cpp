#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld eps = 1e-9;
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
	ld x, y, r;
	int id;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	ld length() const{
		return sqrtl(x*x + y*y);
	}
	ld norm() const{
		return x*x + y*y;
	}
	ld dot(const point & p) const{
		return x * p.x + y * p.y;
	}
	ld cross(const point & p) const{
		return x * p.y - y * p.x;
	}
	point perp() const{
		return point(-y, x);
	}
	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
};

vector<point> convexHull(vector<point> P){
	sort(P.begin(), P.end());
	P.erase(unique(P.begin(), P.end()), P.end());
	vector<point> L, U;
	for(int i = 0; i < P.size(); i++){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

vector<point> tangents(const point & c1, ld r1, const point & c2, ld r2, bool inner){
	if(inner) r2 = -r2;
	point d = c2 - c1;
	ld dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr*dr;
	if(eq(d2, 0) || le(h2, 0)) return {};
	point v = d*dr/d2;
	if(eq(h2, 0)) return {c1 + v*r1};
	else{
		point u = d.perp()*sqrt(h2)/d2;
		point a = c1 + (v - u)*r1; a.id = c1.id;
		point b = c2 + (v - u)*r2; b.id = c2.id;
		point c = c1 + (v + u)*r1; c.id = c1.id;
		point d = c2 + (v + u)*r2; d.id = c2.id;
		return {a, b, c, d};
	}
}

istream &operator>>(istream &is, point & P){
	return is >> P.x >> P.y;
}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

const ld pi = acosl(-1);

ld angle(const point & a, const point & b){
	ld cosine = a.dot(b) / a.length() / b.length();
	int o = sgn(a.cross(b));
	ld ang = acosl(min(1.0l, max(-1.0l, cosine)));
	if(o == -1) return 2.0l*pi - ang;
	else return ang;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			cin >> points[i] >> points[i].r;
			points[i].id = i;
		}
		if(n == 1){
			cout << fixed << setprecision(5) << 2.0l*pi*points[0].r << "\n";
			continue;
		}
		vector<point> poly;
		for(int i = 0; i < n-1; ++i){
			for(int j = i+1; j < n; ++j){
				for(const point & p : tangents(points[i], points[i].r, points[j], points[j].r, false)){
					poly.push_back(p);
				}
			}
		}
		poly = convexHull(poly);
		ld ans = 0;
		for(int i = 0; i < poly.size(); ++i){
			point a = poly[i];
			point b = poly[(i+1) % poly.size()];
			if(a.id == b.id){
				ans += angle(a - points[a.id], b - points[b.id]) * points[a.id].r;
			}else{
				ans += (b - a).length();
			}
		}
		cout << fixed << setprecision(5) << ans << "\n";
	}
	return 0;
}