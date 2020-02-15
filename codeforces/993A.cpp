#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}
	point operator-(const point & p) const{return point(x-p.x, y-p.y);}
	int dot(const point & p) const{return x*p.x + y*p.y;}
	int cross(const point & p) const{return x*p.y - y*p.x;}
};

istream&operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

bool pointInSegment(const point & a, const point & b, const point & p){
	return (p - a).cross(b - a) == 0 && (a - p).dot(b - p) <= 0;
}

bool pointInPerimeter(const vector<point> & P, const point & p){
	int n = P.size();
	for(int i = 0; i < n; i++){
		if(pointInSegment(P[i], P[(i + 1) % n], p)){
			return true;
		}
	}
	return false;
}

bool crossesRay(const point & a, const point & b, const point & p){
	return ((b.y >= p.y) - (a.y >= p.y)) * (a - p).cross(b - p) >= 0;
}

bool pointInPolygon(const vector<point> & P, const point & p){
	if(pointInPerimeter(P, p)){
		return true;
	}
	int n = P.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += crossesRay(P[i], P[(i + 1) % n], p);
	}
	return rays & 1;
}

int sgn(int x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

int intersectSegmentsInfo(const point & a, const point & b, const point & c, const point & d){
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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<point> a(4), b(4);
	for(point & p : a) cin >> p;
	for(point & p : b) cin >> p;
	bool ans = false;
	for(const point & p : a){
		ans = ans | pointInPolygon(b, p);
	}
	for(const point & p : b){
		ans = ans | pointInPolygon(a, p);
	}
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			ans = ans | (intersectSegmentsInfo(a[i], a[(i+1)%4], b[j], b[(j+1)%4]) != 0);
		}
	}
	cout << (ans ? "YES" : "NO") << "\n";
	return 0;
}