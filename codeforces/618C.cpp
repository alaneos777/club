#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	lli dot(const point & p) const{return x*p.x + y*p.y;}
	lli cross(const point & p) const{return x*p.y - y*p.x;}
};

istream&operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

lli area(const point & a, const point & b, const point & c){
	return abs((b - a).cross(c - a));
}

bool pointInside(const point & a, const point & b, const point & c, const point & p){
	return area(a, b, p) + area(b, c, p) + area(c, a, p) == area(a, b, c);
}

bool pointInSegment(const point & a, const point & b, const point & p){
	return (b - a).cross(p - a) == 0 && (a - p).dot(b - p) <= 0;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> points(n);
	for(point & p : points){
		cin >> p;
	}
	int a = 0, b = 1, c = 2;
	for(int i = 2; i < n; ++i){
		if((points[1] - points[0]).cross(points[i] - points[0]) != 0){
			c = i;
			break;
		}
	}
	for(int i = 0; i < n; ++i){
		if(i == a || i == b || i == c) continue;
		if(pointInside(points[a], points[b], points[c], points[i])){
			if(pointInSegment(points[a], points[b], points[i])){
				a = i;
			}else if(pointInSegment(points[b], points[c], points[i])){
				b = i;
			}else if(pointInSegment(points[c], points[a], points[i])){
				c = i;
			}else{
				c = i;
			}
		}
	}
	cout << a+1 << " " << b+1 << " " << c+1 << "\n";
	return 0;
}