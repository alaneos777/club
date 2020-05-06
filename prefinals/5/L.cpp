#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y) {}
	void read(){
		int a, b;
		cin >> a >> b;
		x = a, y = b;
	}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(lli k) const{return point(x*k, y*k);}
	point operator/(lli k) const{return point(x/k, y/k);}
	lli dot(const point & p) const{return x*p.x + y*p.y;}
	lli cross(const point & p) const{return x*p.y - y*p.x;}
	bool operator==(const point & p) const{
		return x == p.x && y == p.y;
	}
	bool operator<(const point & p) const{
		return x < p.x || (x == p.x && y < p.y);
	}
};

struct rect{
	point a, c;
	point b() const{
		return point(c.x, a.y);
	}
	point d() const{
		return point(a.x, c.y);
	}
	vector<point> get() const{
		return {a, b(), c, d()};
	}
	void read(){
		a.read(); c.read();
	}
	bool operator==(const rect & r) const{
		return a == r.a && c == r.c;
	}
};

bool inside(const rect & a, const rect & b){
	//b inside a
	bool test = true;
	for(const point & p : b.get()){
		test &= (a.a.x < p.x && p.x < a.c.x && a.a.y < p.y && p.y < a.c.y);
	}
	return test;
}

bool disjoint(const rect & r1, const rect & r2){
	return r1.c.x <= r2.a.x || r2.c.x <= r1.a.x || r1.a.y >= r2.c.y || r2.a.y >= r1.c.y;
}

int sgn(lli x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

bool pointInLine(const point & a, const point & v, const point & p){
	return (p - a).cross(v) == 0;
}

bool pointInSegment(const point & a, const point & b, const point & p){
	return pointInLine(a, b - a, p) && ((a - p).dot(b - p) <= 0);
}

int info(const point & a, const point & b, const point & c, const point & d){
	point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c));
	}
}

point intersect(const point & a1, const point & v1, const point & a2, const point & v2){
	lli det = v1.cross(v2);
	return a1 + v1 * (a2 - a1).cross(v2) / det;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		rect r1, r2;
		r1.read(), r2.read();
		if(r1 == r2){
			cout << "2\n";
		}else if(inside(r1, r2) || inside(r2, r1)){
			cout << "3\n";
		}else if(disjoint(r1, r2)){
			cout << "3\n";
		}else{
			set<point> V;
			auto p1 = r1.get();
			auto p2 = r2.get();
			vector<set<point>> parts1(4), parts2(4);
			for(int i = 0; i < 4; ++i){
				point a = p1[i], b = p1[(i+1)%4];
				V.insert(a);
				parts1[i].insert(a);
				parts1[i].insert(b);
				for(int j = 0; j < 4; ++j){
					point c = p2[j], d = p2[(j+1)%4];
					V.insert(c);
					parts2[j].insert(c);
					parts2[j].insert(d);
					int res = info(a, b, c, d);
					if(res == 1){
						point p = intersect(a, b-a, c, d-c);
						V.insert(p);
						parts1[i].insert(p);
						parts2[j].insert(p);
					}else if(res == -1){
						vector<point> tmp = {a, b, c, d};
						if(pointInSegment(a, b, c)){
							parts1[i].insert(c);
						}
						if(pointInSegment(a, b, d)){
							parts1[i].insert(c);
						}
						if(pointInSegment(c, d, a)){
							parts2[j].insert(a);
						}
						if(pointInSegment(c, d, b)){
							parts2[j].insert(b);
						}
					}
				}
			}
			set<pair<point, point>> E;
			for(int i = 0; i < 4; ++i){
				point prev = *parts1[i].begin();
				for(const point & p : parts1[i]){
					point U = prev, V = p;
					if(V < U) swap(U, V);
					if(!(U == V)) E.emplace(U, V);
					prev = p;
				}
				prev = *parts2[i].begin();
				for(const point & p : parts2[i]){
					point U = prev, V = p;
					if(V < U) swap(U, V);
					if(!(U == V)) E.emplace(U, V);
					prev = p;
				}
			}
			cout << E.size() + 2 - V.size() << "\n";
		}
	}
	return 0;
}