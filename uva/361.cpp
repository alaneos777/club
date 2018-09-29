#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}
	void read(){cin >> x >> y;}

	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	bool operator==(const point & p) const{
		return x == p.x && y == p.y;
	}

	bool operator<(const point & p) const{
		if(x == p.x) return y < p.y;
		return x < p.x;
	}

	bool operator>(const point & p) const{
		if(x == p.x) return y > p.y;
		return x > p.x;
	}

	int cross(const point & p) const{
		return x * p.y - y * p.x;
	}
};

vector<point> convexHull(vector<point> & points){
	if(points.size() <= 2) return points;
	sort(points.begin(), points.end());
	vector<point> L, U;
	for(int i = 0; i < points.size(); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - points[i]).cross(L[L.size() - 1] - points[i]) <= 0){
			L.pop_back();
		}
		L.push_back(points[i]);
	}
	for(int i = points.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - points[i]).cross(U[U.size() - 1] - points[i]) <= 0){
			U.pop_back();
		}
		U.push_back(points[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

int area2(const vector<point> & points){
	int n = points.size();
	int ans = 0;
	for(int i = 0; i < n; i++){
		ans += points[i].cross(points[(i + 1) % n]);
	}
	return abs(ans);
}

bool pointInLine(point & a, point & b, point & p){
	return abs((p - a).cross(b - a)) == 0;
}

bool pointInSegment(point a, point b, point & p){
	if(a > b) swap(a, b);
	return pointInLine(a, b, p) && !(p < a || p > b);
}

bool pointInPolygon(vector<point> & polygon, int area_polygon, point & p){
	int n = polygon.size();
	int area = 0;
	if(n == 0){
		return false;
	}else if(n == 1){
		return p == polygon[0];
	}else if(n == 2){
		return pointInSegment(polygon[0], polygon[1], p);
	}
	for(int i = 0; i < n; i++){
		area += area2({p, polygon[i], polygon[(i + 1) % n]});
	}
	return area == area_polygon;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int c, r, o, caso = 0;
	while(cin >> c >> r >> o && !(c == 0 && r == 0 && o == 0)){
		vector<point> cops(c), robbers(r), citizens(o);
		for(int i = 0; i < c; ++i) cops[i].read();
		for(int i = 0; i < r; ++i) robbers[i].read();
		for(int i = 0; i < o; ++i) citizens[i].read();
		cops = convexHull(cops);
		robbers = convexHull(robbers);
		int area_cops = area2(cops);
		int area_robbers = area2(robbers);
		cout << "Data set " << ++caso << ":\n";
		for(int i = 0; i < o; ++i){
			cout << "     Citizen at (" << citizens[i].x << "," << citizens[i].y << ") is ";
			if(pointInPolygon(cops, area_cops, citizens[i]) && c >= 3){
				cout << "safe.\n";
			}else if(pointInPolygon(robbers, area_robbers, citizens[i]) && r >= 3){
				cout << "robbed.\n";
			}else{
				cout << "neither.\n";
			}
		}
		cout << "\n";
	}
	return 0;
}