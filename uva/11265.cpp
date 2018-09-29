#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct point{
	double x, y;
	point(): x(0), y(0){}
	point(double x, double y): x(x), y(y){}

	double cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	point operator+(const point & p) const{
		return point(x + p.x, y + p.y);
	}

	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	point operator*(const double & k) const{
		return point(x * k, y * k);
	}

	bool operator==(const point & p) const{
		return abs(x - p.x) < eps && abs(y - p.y) < eps;
	}

	bool operator<(const point & p) const{
		if(abs(x - p.x) < eps) return y < p.y;
		return x < p.x;
	}
	bool operator>(const point & p) const{
		if(abs(x - p.x) < eps) return y > p.y;
		return x > p.x;
	}
};

istream &operator>>(istream &is, point & P){
	point p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

int sgn(double x){
	if(abs(x) < eps){
		return 0;
	}else if(x > 0){
		return 1;
	}else{
		return -1;
	}
}

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	double det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

int intersectLineSegmentInfo(const point & a, const point & v, const point & c, const point & d){
	//line a+tv, segment cd
	point v2 = d - c;
	double det = v.cross(v2);
	if(abs(det) < eps){
		if(abs((c - a).cross(v)) < eps){
			return -1; //infinity points
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a)); //1: single point, 0: no point
	}
}

bool pointInLine(const point & a, const point & v, const point & p){
	//line a+tv, point p
	return abs((p - a).cross(v)) < eps;
}

bool pointInSegment(point a, point b, const point & p){
	//segment ab, point p
	if(a > b) swap(a, b);
	return pointInLine(a, b - a, p) && !(p < a || p > b);
}

int intersectSegmentsInfo(const point & a, const point & b, const point & c, const point & d){
	//segment ab, segment cd
	point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no point
			}
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single point, 0: no point
	}
}

bool lineCutsPolygon(vector<point> & P, const point & a, const point & v){
	//line a+tv, polygon P
	int n = P.size();
	for(int i = 0, first = 0; i <= n; ++i){
		int side = sgn(v.cross(P[i%n]-a));
		if(!side) continue;
		if(!first) first = side;
		else if(side != first) return true;
	}
	return false;
}

vector<vector<point>> cutPolygon(vector<point> & P, const point & a, const point & v){
	//line a+tv, polygon P
	int n = P.size();
	if(!lineCutsPolygon(P, a, v)) return {P};
	int idx = 0;
	vector<vector<point>> ans(2);
	for(int i = 0; i < n; ++i){
		if(intersectLineSegmentInfo(a, v, P[i], P[(i+1)%n])){
			point p = intersectLines(a, v, P[i], P[(i+1)%n] - P[i]);
			if(P[i] == p) continue;
			ans[idx].push_back(P[i]);
			ans[1-idx].push_back(p);
			ans[idx].push_back(p);
			idx = 1-idx;
		}else{
			ans[idx].push_back(P[i]);
		}
	}
	return ans;
}

int pointInPolygon(vector<point> & P, const point & p){
	point bottomLeft = (*min_element(P.begin(), P.end())) - point(M_E, M_PI);
	int n = P.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += (intersectSegmentsInfo(p, bottomLeft, P[i], P[(i + 1) % n]) == 1 ? 1 : 0);
	}
	return rays & 1; //0: point outside, 1: point inside
}

double area(vector<point> & P){
	int n = P.size();
	double ans = 0;
	for(int i = 0; i < n; i++){
		ans += P[i].cross(P[(i + 1) % n]);
	}
	return abs(ans / 2);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, caso = 1;
	double w, h;
	point fountain, a, b;
	while(cin >> n >> w >> h >> fountain){
		vector<point> polygon = {{0, 0}, {w, 0}, {w, h}, {0, h}};
		for(int i = 0; i < n; ++i){
			cin >> a >> b;
			vector<vector<point>> polygons = cutPolygon(polygon, a, b - a);
			if(pointInPolygon(polygons[0], fountain)){
				polygon = polygons[0];
			}else{
				polygon = polygons[1];
			}
		}
		cout << fixed << setprecision(3) << "Case #" << caso++ << ": " << area(polygon) << "\n";
	}
	return 0;
}