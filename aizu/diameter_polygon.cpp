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

double dist(const point & a, const point & v, const point & p){
	return abs(v.cross(p - a)) / v.length();
}

double diameter(vector<point> & P){
	int n = P.size(), k = 0;
	auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
	auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
	double diameter = numeric_limits<double>::min();
	while(dot(0, k) > eps) k = (k+1) % n;
	for(int i = 0; i < n; ++i){
		while(cross(i, k) > eps) k = (k+1) % n;
		//pair: (i, k)
		diameter = max(diameter, (P[k] - P[i]).length());
	}
	return diameter;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, caso = 1;
	cin >> n;
	vector<point> points(n);
	for(int i = 0; i < n; ++i){
		points[i].read();
	}
	cout << fixed << setprecision(10) << diameter(points) << "\n";
	return 0;
}