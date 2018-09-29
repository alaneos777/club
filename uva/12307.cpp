#include <bits/stdc++.h>
using namespace std;
typedef double ld;
ld eps = 1e-9;

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}
	void read(){cin >> x >> y;}

	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	ld cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	ld dot(const point & p) const{
		return x * p.x + y * p.y;
	}

	point perp() const{
		return point(-y ,x);
	}

	bool operator<(const point & p) const{
		if(abs(x - p.x) >= eps) return x < p.x;
		return y < p.y;
	}

	ld length() const{
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

double distancePointLine(const point & a, const point & v, const point & p){
	return abs(v.cross(p - a)) / v.length();
}

pair<double, double> smallestRectangle(vector<point> & points){
	int n = points.size();

	auto dot = [&](int a, int b){return (points[(a+1)%n]-points[a]).dot(points[(b+1)%n]-points[b]);};
	auto cross = [&](int a, int b){return (points[(a+1)%n]-points[a]).cross(points[(b+1)%n]-points[b]);};
	ld perimeter = numeric_limits<ld>::max(), area = perimeter;

	for(int i = 0, j = 0, k = 0, m = 0; i < n; ++i){
		while(dot(i, j) > eps) j = (j + 1) % n;
		if(!i) k = j;
		while(cross(i, k) > eps) k = (k + 1) % n;
		if(!i) m = k;
		while(dot(i, m) < -eps) m = (m + 1) % n;
		//pairs: (i, k) , (j, m)
		point v = points[(i+1)%n] - points[i];
		ld d1 = distancePointLine(points[i], v, points[k]);
		ld d2 = distancePointLine(points[j], v.perp(), points[m]);
		perimeter = min(perimeter, 2 * (d1 + d2));
		area = min(area, d1 * d2);
	}
	return make_pair(area, perimeter);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n && n != 0){
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			points[i].read();
		}
		points = convexHull(points);
		auto ans = smallestRectangle(points);
		cout << fixed << setprecision(2) << ans.first << " " << ans.second << "\n";
	}
	return 0;
}