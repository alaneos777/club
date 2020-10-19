#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}
	bool operator==(const point & p) const{return x == p.x && y == p.y;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
	bool operator<=(const point & p) const{return *this < p || *this == p;}
};

int sgn(lli x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

bool pointInLine(const point & a, const point & v, const point & p){
	return (p - a).cross(v) == 0;
}

bool pointInSegment(const point & a, const point & b, const point & p){
	return pointInLine(a, b - a, p) && (a - p).dot(b - p) <= 0;
}

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

const lli INF = lli(1e18) * lli(1e18) * 100;
const pair<point, point> inf = {{-INF, -INF}, {-INF, -INF}};

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	lli num = (a2 - a1).cross(v2), den = v1.cross(v2);
	if(v1.x * num % den != 0 || v1.y * num % den != 0) return {-INF, -INF};
	return a1 + point(v1.x * num / den, v1.y * num / den);
}

pair<point, point> intersectSegments(const point & a, const point & b, const point & c, const point & d){
	if(c == d){
		return pointInSegment(a, b, c) ? make_pair(c, c) : inf;
	}else if(a == b){
		return pointInSegment(c, d, a) ? make_pair(a, a) : inf;
	}
	point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				if(a <= c && c <= b && b <= d) return {c, b};
				else if(c <= a && a <= d && d <= b) return {a, d};
				else if(a <= c && d <= b) return {c, d};
				else if(c <= a && b <= d) return {a, b};
				assert(0);
				return inf;
			}else{
				return inf;
			}
		}else{
			return inf;
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)) ? make_pair(intersectLines(a, b - a, c, d - c), intersectLines(a, b - a, c, d - c)) : inf;
	}
}

auto intersectSQ(const set<pair<point, point>> & lhs, const set<pair<point, point>> & rhs){
	set<pair<point, point>> ans;
	for(const auto & seg_a : lhs){
		for(const auto & seg_b : rhs){
			auto nuevo = intersectSegments(seg_a.first, seg_a.second, seg_b.first, seg_b.second);
			if(nuevo != inf){
				ans.insert(nuevo);
			}
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	set<pair<point, point>> ans;
	for(int i = 0; i < n; ++i){
		int x, y, r;
		cin >> x >> y >> r;
		point curr(x, y);
		if(i >= 1 && ans.empty()) continue;
		if(r == 0){
			set<pair<point, point>> st = {{curr, curr}};
			if(i == 0){
				ans = st;
			}else{
				ans = intersectSQ(ans, st);
			}
		}else{
			point a(x + r, y);
			point b(x, y + r);
			point c(x - r, y);
			point d(x, y - r);
			set<pair<point, point>> st = {{min(a, b), max(a, b)}, {min(b, c), max(b, c)}, {min(c, d), max(c, d)}, {min(d, a), max(d, a)}};
			if(i == 0){
				ans = st;
			}else{
				ans = intersectSQ(ans, st);
			}
		}
	}
	if(ans.empty()){
		cout << "impossible\n";
	}else{
		if(ans.size() == 1){
			auto seg = *ans.begin();
			if(seg.first == seg.second){
				cout << seg.first.x << " " << seg.first.y << "\n";
			}else{
				cout << "uncertain\n";
			}
		}else{
			cout << "uncertain\n";
		}
	}
	return 0;
}