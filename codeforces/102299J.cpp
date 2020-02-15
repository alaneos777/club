#include <bits/stdc++.h>
using namespace std;
using ld = long double;
ld eps = 1e-9, inf = numeric_limits<ld>::max();

bool le(ld a, ld b){return b-a > eps;}
bool ge(ld a, ld b){return a-b > eps;}
bool eq(ld a, ld b){return abs(a-b) <= eps;}

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}
	point perpendicular() const{
		return point(-y, x);
	}
	ld cross(const point & p) const{
		return x * p.y - y * p.x;
	}
	ld norm() const{
		return x * x + y * y;
	}
	ld length() const{
		return sqrtl(x * x + y * y);
	}
};

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

pair<point, ld> getCircle(const point & m, const point & n, const point & p){
	point c = intersectLines((n + m) / 2, (n - m).perpendicular(), (p + n) / 2, (p - n).perpendicular());
	ld r = (c - m).length();
	return {c, r};
}

pair<point, ld> mec2(vector<point> & S, const point & a, const point & b, int n){
	ld hi = inf, lo = -hi;
	for(int i = 0; i < n; ++i){
		ld si = (b - a).cross(S[i] - a);
		if(eq(si, 0)) continue;
		point m = getCircle(a, b, S[i]).first;
		ld cr = (b - a).cross(m - a);
		if(le(si, 0)) hi = min(hi, cr);
		else lo = max(lo, cr);
	}
	ld v = (ge(lo, 0) ? lo : le(hi, 0) ? hi : 0);
	point c = (a + b) / 2 + (b - a).perpendicular() * v / (b - a).norm();
	return {c, (a - c).norm()};
}

pair<point, ld> mec(vector<point> & S, const point & a, int n){
	random_shuffle(S.begin(), S.begin() + n);
	point b = S[0], c = (a + b) / 2;
	ld r = (a - c).norm();
	for(int i = 1; i < n; ++i){
		if(ge((S[i] - c).norm(), r)){
			tie(c, r) = (n == S.size() ? mec(S, S[i], i) : mec2(S, a, S[i], i));
		}
	}
	return {c, r};
}

pair<point, ld> smallestEnclosingCircle(vector<point> S){
	assert(!S.empty());
	auto r = mec(S, S[0], S.size());
	return {r.first, r.second / 2};
}

istream& operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

ostream& operator<<(ostream & os, const point & p){
	return os << p.x << " " << p.y;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> points(n);
	for(point & p : points){
		cin >> p;
	}
	auto ans = smallestEnclosingCircle(points);
	cout << fixed << setprecision(7) << ans.first << " " << ans.second << "\n";
	return 0;
}