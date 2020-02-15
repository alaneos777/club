#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

using ld = double;
const ld eps = 1e-9;
bool eq(ld a, ld b){return abs(a-b)<eps;}
bool le(ld a, ld b){return a-b<-eps;}
bool ge(ld a, ld b){return a-b>eps;}

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x*k, y*k);}
	point operator/(const ld & k) const{return point(x/k, y/k);}
	ld cross(const point & p) const{return x*p.y - y*p.x;}
	bool operator<(const point & p) const{
		if(!eq(x,p.x)) return le(x, p.x);
		return le(y, p.y);
	}
};

bool intersect(const point & a, const point & b, const point & c, const point & d, point & out){
	point v1 = b-a, v2 = d-c;
	ld den = v1.cross(v2);
	if(eq(den, 0)) return false;
	ld t = (c-a).cross(v2) / den;
	ld u = (c-a).cross(v1) / den;
	if(!(ge(t, 0) && le(t, 1) && ge(u, 0) && le(u, 1))) return false;
	out = a + v1*t;
	return true;
}

int main(){
	int first = 0;
	int n = 20000;
	vector<point> points(n/2);
	set<point> conj;
	lli sn = 290797;
	for(int i = 1; i <= n; ++i){
		sn = sn * sn % 50515093;
		int tn = sn % 500;
		if(i % 2 == 1) points[(i-1)/2].x = tn;
		else points[(i-1)/2].y = tn;
	}
	for(int i = 0; i < n/2; i += 2){
		for(int j = i+2; j < n/2; j += 2){
			point a = points[i];
			point b = points[i+1];
			point c = points[j];
			point d = points[j+1];
			point out;
			if(intersect(a, b, c, d, out)){
				conj.insert(out);
			}
		}
	}
	cout << conj.size() << "\n";
	return 0;
}