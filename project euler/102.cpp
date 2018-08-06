#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;
# define M_PI 3.14159265358979323846
# define M_E 2.71828182845904523536

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
	double cross(const point & p) const{
		return x * p.y - y * p.x;
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

int sgn(double x){
	if(abs(x) < eps){
		return 0;
	}else if(x > 0){
		return 1;
	}else{
		return -1;
	}
}

bool pointInLine(point & a, point & b, point & p){
	//line ab, point p
	return abs((p - a).cross(b - a)) < eps;
}

bool pointInSegment(point a, point b, point & p){
	//segment ab, point p
	if(a > b) swap(a, b);
	return pointInLine(a, b, p) && !(p < a || p > b);
}

int intersectSegmentsInfo(point & a, point & b, point & c, point & d){
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

bool pointInPerimeter(vector<point> & points, point & p){
	int n = points.size();
	for(int i = 0; i < n; i++){
		if(pointInSegment(points[i], points[(i + 1) % n], p)){
			return true;
		}
	}
	return false;
}

int pointInPolygon(vector<point> & points, point & p){
	if(pointInPerimeter(points, p)){
		return -1; //point in the perimeter
	}
	point bottomLeft = (*min_element(points.begin(), points.end())) - point(M_E, M_PI);
	int n = points.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += (intersectSegmentsInfo(p, bottomLeft, points[i], points[(i + 1) % n]) == 1 ? 1 : 0);
	}
	return rays & 1; //0: point outside, 1: point inside
}

istream &operator>>(istream &is, point & P){
	point p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

int main(){
	ifstream in("p102_triangles.txt");
	vector<point> triangle(3);
	point origin(0, 0);
	int ans = 0;
	while(in >> triangle[0] >> triangle[1] >> triangle[2]){
		if(pointInPolygon(triangle, origin)) ans++;
	}
	cout << ans << "\n";
	return 0;
}