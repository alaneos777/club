#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;

struct point{
	double x, y;
	point(): x(0), y(0) {}
	point(double x, double y): x(x), y(y) {}
	void read(){cin >> x >> y;}

	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator/(const double & k) const{return point(x / k, y / k);}
	bool operator<(const point & p) const{
		if(abs(x - p.x) < eps){
			return y < p.y;
		}else{
			return x < p.x;
		}
	}
	double cross(const point & p) const{
		return x * p.y - y * p.x;
	}
	double length() const{
		return hypot(x, y);
	}
};

vector<point> convexHull(vector<point> & P){
	sort(P.begin(), P.end());
	vector<point> L, U;
	for(int i = 0; i < P.size(); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]) <= 0){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]) <= 0){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

double dist(const point & a, const point & v, const point & p){
	return abs(v.cross(p - a));
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, caso = 1;
	while(cin >> n && n != 0){
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			points[i].read();
		}
		points = convexHull(points);
		n = points.size();
		double ans = 1e10;
		for(int i = 0; i < n; ++i){
			point a = points[i];
			point b = points[(i+1)%n];
			point v = b - a;
			v = v / v.length();
			double maxD = 0;
			for(point & p : points){
				maxD = max(maxD, dist(a, v, p));
			}
			ans = min(maxD, ans);
		}
		cout << fixed << setprecision(2) << "Case " << caso++ << ": " << ans << "\n";
	}
	return 0;
}