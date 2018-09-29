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
	double dot(const point & p) const{
		return x * p.x + y * p.y;
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
	return abs(v.cross(p - a)) / v.length();
}

double width(vector<point> & P){
	int n = P.size(), k = 0;
	auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
	auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
	double width = numeric_limits<double>::max();
	while(dot(0, k) > eps) k = (k+1) % n;
	for(int i = 0; i < n; ++i){
		while(cross(i, k) > eps) k = (k+1) % n;
		width = min(width, dist(P[i], P[(i+1)%n] - P[i], P[k]));
	}
	return width;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, r;
	while(cin >> n >> r){
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			points[i].read();
		}
		points = convexHull(points);
		cout << fixed << setprecision(11) << width(points) << "\n";
	}
	return 0;
}