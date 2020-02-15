#include <bits/stdc++.h>
using namespace std;

struct point{
	int x, y;
	point(): x(0), y(0) {}
	point(int x, int y): x(x), y(y) {}
	int cross(const point & p) const{return x * p.y - y * p.x;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
	bool operator==(const point & p) const{return x == p.x && y == p.y;}
};

struct hsh{
	size_t operator()(const point & p) const{
		return hash<int>()(p.x ^ (p.y << 16));
	}
};

int main(){
	int n = 2500;
	int64_t s = 290797;
	vector<point> points(n);
	for(int i = 0; i < 2*n; ++i){
		s = s * s % 50515093;
		int t = (s % 2000) - 1000;
		if(i & 1) points[i>>1].y = t;
		else points[i>>1].x = t;
	}
	unordered_map<point, set<int>, hsh> lines;
	for(int i = 0; i < n-1; ++i){
		for(int j = i+1; j < n; ++j){
			int a = points[j].y - points[i].y;
			int b = points[i].x - points[j].x;
			int c = points[i].cross(points[j]);
			int d = __gcd(__gcd(abs(a), abs(b)), abs(c));
			a /= d, b /= d, c /= d;
			if(a < 0){
				a = -a, b = -b, c = -c;
			}else if(a == 0 && b < 0){
				b = -b, c = -c;
			}
			lines[{a, b}].insert(c);
		}
	}
	int64_t M = 0, S = 0;
	for(auto v : lines){
		M += v.second.size();
	}
	for(auto v : lines){
		S += (M - v.second.size()) * v.second.size();
	}
	cout << M << " " << S << "\n";
	return 0;
}