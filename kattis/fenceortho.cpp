#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}
	void read(){cin >> x >> y;}

	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	int cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	int dot(const point & p) const{
		return x * p.x + y * p.y;
	}

	bool operator<(const point & p) const{
		if(x != p.x) return x < p.x;
		return y < p.y;
	}

	double length() const{
		return hypot(x, y);
	}
};

vector<point> convexHull(vector<point> & points){
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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n){
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			points[i].read();
		}
		points = convexHull(points);
		n = points.size();
		double perimeter = 1e10;
		for(int i = 0; i < n; ++i){
			point a = points[i], b = points[(i+1)%n];
			point v = b - a;
			int height = 0, width_m = 0, width_M = 0, width = 0;
			for(int j = 0; j < n; ++j){
				point p = points[j];
				height = max(height, v.cross(p - a));
				width = v.dot(p - a);
				width_m = min(width_m, width);
				width_M = max(width_M, width);
			}
			perimeter = min(perimeter, (double)(2 * height + 2 * (width_M - width_m)) / v.length());
		}
		cout << fixed << setprecision(10) << perimeter << "\n";
	}
	return 0;
}