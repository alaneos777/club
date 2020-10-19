#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(lli k) const{return point(x*k, y*k);}
	bool operator<(const point & p) const{return (x < p.x) || ((x == p.x) && (y < p.y));}
};

int t;

struct rect{
	point a, b, c, d;
	char dir;
	int v;
	vector<point> getFront() const{
		if(dir == 'E') return {b, c};
		if(dir == 'N') return {d, c};
		if(dir == 'W') return {a, d};
		if(dir == 'S') return {a, b};
	}
	vector<point> getBack() const{
		if(dir == 'E') return {a, d};
		if(dir == 'N') return {a, b};
		if(dir == 'W') return {b, c};
		if(dir == 'S') return {d, c};
	}
	point getDir() const{
		if(dir == 'E') return point(1, 0);
		if(dir == 'N') return point(0, 1);
		if(dir == 'W') return point(-1, 0);
		if(dir == 'S') return point(0, -1);
	}
	vector<point> get() const{
		return {getBack()[0], getBack()[1], getFront()[0] + getDir()*v*t, getFront()[1] + getDir()*v*t};
	}
};

ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> t;
	char d1, d2;
	point c1, c2;
	int v1, v2;
	int w1, w2;
	int h1, h2;
	cin >> d1 >> c1.x >> c1.y >> v1 >> h1 >> w1;
	cin >> d2 >> c2.x >> c2.y >> v2 >> h2 >> w2;
	rect r1;
	r1.dir = d1;
	r1.v = v1*2;
	r1.a = c1*2 + point{-h1, -w1};
	r1.b = c1*2 + point{h1, -w1};
	r1.c = c1*2 + point{h1, w1};
	r1.d = c1*2 + point{-h1, w1};
	rect r2;
	r2.dir = d2;
	r2.v = v2*2;
	r2.a = c2*2 + point{-h2, -w2};
	r2.b = c2*2 + point{h2, -w2};
	r2.c = c2*2 + point{h2, w2};
	r2.d = c2*2 + point{-h2, w2};
	//cout << r1.a << r1.c << "\n";
	//cout << r2.a << r2.c << "\n";
	auto m = r1.get();
	auto n = r2.get();
	sort(m.begin(), m.end());
	sort(n.begin(), n.end());
	int left = max(m[0].x, n[0].x);
	int right = min(m[3].x, n[3].x);
	int bottom = max(m[0].y, n[0].y);
	int top = min(m[3].y, n[3].y);
	//cout << n[0] << " " << n[1] << " " << n[2] << " " << n[3] << "\n";
	if(left <= right && bottom <= top){
		int area = (right - left) * (top - bottom);
		if(area > 0) cout << "crash\n";
		else cout << "safe\n";
	}
	else cout << "safe\n";
	return 0;
}