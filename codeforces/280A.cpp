#include <bits/stdc++.h>
using namespace std;
# define M_PI 3.14159265358979323846

double eps = 1e-8;

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

istream &operator>>(istream &is, point & P){
	point p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

ostream &operator<<(ostream &os, const point & p) { 
    return os << fixed << setprecision(2) << "(" << p.x << " " << p.y << ")";
}

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

int main(){
	ios_base::sync_with_stdio(0);
	double w, h, a;
	cin >> w >> h >> a;
	if(a > 90) a = 180 - a;
	a *= M_PI / 180;
	if(w < h) swap(w, h);
	double limit = 2 * atan(h / w);
	point A = point(w / 2, h / 2), B = point(-w / 2, h / 2), C = point(-w / 2, -h / 2), D = point(w / 2, -h / 2);
	point AR = A.rotate(a), BR = B.rotate(a), CR = C.rotate(a), DR = D.rotate(a);
	if(a == 0){
		cout << fixed << setprecision(10) << w * h << "\n";
	}else if(a < limit){
		vector<point> pol(8);
		pol[0] = intersect(A, B, DR, AR);
		pol[1] = intersect(A, B, AR, BR);
		pol[2] = intersect(B, C, AR, BR);
		pol[3] = intersect(B, C, BR, CR);
		pol[4] = intersect(C, D, BR, CR);
		pol[5] = intersect(C, D, CR, DR);
		pol[6] = intersect(D, A, CR, DR);
		pol[7] = intersect(D, A, DR, AR);
		cout << fixed << setprecision(10) << area(pol) << "\n";
	}else{
		vector<point> pol(4);
		pol[0] = intersect(A, B, CR, DR);
		pol[1] = intersect(A, B, AR, BR);
		pol[2] = intersect(C, D, AR, BR);
		pol[3] = intersect(C, D, CR, DR);
		cout << fixed << setprecision(10) << area(pol) << "\n";
	}
	return 0;
}