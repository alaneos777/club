#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;

struct point{
	double x, y, r;
	point(): x(0), y(0){}
	point(double x, double y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}

	point operator-(const point & p) const{return point(x - p.x, y - p.y);}

	point operator*(const double & k) const{return point(x * k, y * k);}

	point operator/(const double & k) const{return point(x / k, y / k);}

	double length() const{
		return hypot(x, y);
	}
	double cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	point normalize() const{
		return (*this) / length();
	}

	point perpendicular() const{
		return point(-y, x);
	}
	point rotate(const double angle) const{
		return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
	}

	bool operator<(const point & p) const{
		return x-r < p.x-p.r;
	}
};

istream &operator>>(istream &is, point & P){
	point p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

vector<point> convexHull(vector<point> & P){
	sort(P.begin(), P.end());
	vector<point> pos, neg;
	for(point & p : P){
		
	}
}

pair<point, point> pointsOfTangency(const point & p, const point & c, double r){
	//point p (outside the circle), center c, radius r
	point v = (p - c).normalize() * r;
	double theta = acos(r / (p - c).length());
	return {c + v.rotate(-theta), c + v.rotate(theta)};
}

int circleInsideCircle(const point & c1, double r1, const point & c2, double r2){
	//test if circle 2 is inside circle 1
	//returns "-1" if 2 touches internally 1, "1" if 2 is inside 1, "0" if they overlap
	double l = r1 - r2 - (c1 - c2).length();
	return (l > eps ? 1 : (abs(l) < eps ? -1 : 0));
}

vector<vector<point>> commonExteriorTangents(const point & c1, double r1, const point & c2, double r2){
	//returns a vector of segments or a single point
	if(r1 < r2) return commonExteriorTangents(c2, r2, c1, r1);
	if(c1 == c2 && abs(r1-r2) < 0) return {};
	int in = circleInsideCircle(c1, r1, c2, r2);
	if(in == 1) return {};
	else if(in == -1) return {{c1 + (c2 - c1).normalize() * r1}};
	else{
		pair<point, point> t;
		if(abs(r1-r2) < eps)
			t = {c1 - (c2 - c1).perpendicular(), c1 + (c2 - c1).perpendicular()};
		else
			t = pointsOfTangency(c2, c1, r1 - r2);
		t.first = (t.first - c1).normalize();
		t.second = (t.second - c1).normalize();
		return {{c1 + t.first * r1, c2 + t.first * r2}, {c1 + t.second * r1, c2 + t.second * r2}};
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		vector<point> points(n);
		for(int i = 0; i < n; ++i){
			cin >> points[i];
			cin >> points[i].r;
		}
		points = convexHull(points);
		//
	}
	return 0;
}