#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;

bool geq(double a, double b){return a-b >= -eps;}     //a >= b
bool ge(double a, double b){return a-b > eps;}        //a > b
bool eq(double a, double b){return abs(a-b) <= eps;}  //a == b
bool leq(double a, double b){return b-a >= -eps;}     //a <= b

struct point{
	double x, y;
	point(): x(0), y(0){}
	point(double x, double y): x(x), y(y){}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	double dot(const point & p) const{return x * p.x + y * p.y;}
	double cross(const point & p) const{return x * p.y - y * p.x;}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}

bool pointInLine(const point & a, const point & v, const point & p){
	//line a+tv, point p
	return eq((p - a).cross(v), 0);
}

bool pointInSegment(const point & a, const point & b, const point & p){
	//segment ab, point p
	return pointInLine(a, b - a, p) && leq((a - p).dot(b - p), 0);
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
	return ge((geq(b.y, p.y) - geq(a.y, p.y)) * (a - p).cross(b - p), 0);
}

int pointInPolygon(vector<point> & P, const point & p){
	if(pointInPerimeter(P, p)){
		return -1; //point in the perimeter
	}
	int n = P.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += crossesRay(P[i], P[(i + 1) % n], p);
	}
	return rays & 1; //0: point outside, 1: point inside
}

int main(){
	ios_base::sync_with_stdio(0);
	int n;
	while(cin >> n && n != 0){
		vector<point> polygon(n);
		for(int i = 0; i < n; i++){
			cin >> polygon[i];
		}
		point p;
		cin >> p;
		if(pointInPolygon(polygon, p) != 0){
			cout << "T\n";
		}else{
			cout << "F\n";
		}
	}
	return 0;
}