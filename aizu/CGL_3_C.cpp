#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	int dot(const point & p) const{return x * p.x + y * p.y;}
	int cross(const point & p) const{return x * p.y - y * p.x;}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}

bool pointInLine(const point & a, const point & v, const point & p){
	return (p - a).cross(v) == 0;
}

bool pointInSegment(const point & a, const point & b, const point & p){
	return pointInLine(a, b - a, p) && (a - p).dot(b - p) <= 0;
}

bool pointInPerimeter(vector<point> & P, const point & p){
	int n = P.size();
	for(int i = 0; i < n; i++){
		if(pointInSegment(P[i], P[(i + 1) % n], p)){
			return true;
		}
	}
	return false;
}

bool crossesRay(const point & a, const point & b, const point & p){
	return ((b.y >= p.y) - (a.y >= p.y)) * (a - p).cross(b - p) > 0;
}

int pointInPolygon(vector<point> & P, const point & p){
	if(pointInPerimeter(P, p)){
		return 1; //1: point in the perimeter
	}
	int n = P.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += crossesRay(P[i], P[(i + 1) % n], p);
	}
	return (rays & 1) ? 2 : 0; //0: point outside, 2: point inside
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n;
	vector<point> polygon(n);
	for(int i = 0; i < n; i++){
		cin >> polygon[i];
	}
	cin >> q;
	while(q--){
		point p;
		cin >> p;
		cout << pointInPolygon(polygon, p) << "\n";
	}
	return 0;
}