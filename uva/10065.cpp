#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;
# define M_PI 3.14159265358979323846

struct point{
	double x, y;

	point(){
		x = y = 0;
	}
	point(double x, double y){
		this->x = x, this->y = y;
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
	point operator/(const double & k) const{
		return point(x / k, y / k);
	}

	point rotate(const double angle) const{
		return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
	}
	point rotate(const double angle, const point & p){
		return p + ((*this) - p).rotate(angle);
	}

	double dot(const point & p) const{
		return x * p.x + y * p.y;
	}
	double length() const{
		return sqrt(this->dot(*this));
	}
	double cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	point normalize() const{
		return (*this) / length();
	}

	double angle() const{
		return acos(x / length());
	}
	point projection(const point & p) const{
		return (*this) * p.dot(*this) / dot(*this);
	}
	point normal(const point & p) const{
		return p - projection(p);
	}

	bool operator==(const point & p) const{
		return abs(x - p.x) < eps && abs(y - p.y) < eps;
	}
	bool operator!=(const point & p) const{
		return !(*this == p);
	}
	bool operator<(const point & p) const{
		if(abs(x - p.x) < eps){
			return y < p.y;
		}else{
			return x < p.x;
		}
	}
	bool operator>(const point & p) const{
		if(abs(x - p.x) < eps){
			return y > p.y;
		}else{
			return x > p.x;
		}
	}
};

point intersect(point & a, point & b, point & c, point & d){
	point v1 = b - a, v2 = d - c;
	return a + v1 * ((c - a).cross(v2) / v1.cross(v2));
}

double area(vector<point> & points){
	int n = points.size();
	double ans = 0;
	for(int i = 0; i < n; i++){
		ans += points[i].cross(points[(i + 1) % n]);
	}
	return abs(ans / 2);
}

vector<point> convexHull(vector<point> points){
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

istream &operator>>(istream &is, point & P){
	point p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

ostream &operator<<(ostream &os, const point & p) { 
    return os << fixed << setprecision(2) << p.x << " " << p.y;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, count = 1;
	while(cin >> n && n != 0){
		vector<point> figure(n);
		while(n--){
			cin >> figure[n];
		}
		vector<point> container = convexHull(figure);
		cout << "Tile #" << (count++) << "\n";
		for(int i = 0; i < container.size(); i++){
		}
		cout << fixed << setprecision(2) << "Wasted Space = " << (100 - area(figure) / area(container) * 100) << " %\n\n";
	}
	return 0;
}