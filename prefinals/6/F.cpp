#include <bits/stdc++.h>
using namespace std;
using lli = long long;

struct point{
	lli x, y;
	int i, j;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const lli & k) const{return point(x * k, y * k);}
	point perp() const{return point(-y, x);}
	lli dot(const point & p) const{return x * p.x + y * p.y;}
	lli cross(const point & p) const{return x * p.y - y * p.x;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
	bool half(const point & p) const{return p.cross(*this) < 0 || (p.cross(*this) == 0 && p.dot(*this) < 0);}
};

void polarSort(vector<point> & P, const point & o, const point & v){
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		return point((a - o).half(v), 0) < point((b - o).half(v), (a - o).cross(b - o));
	});
}

lli getArea(const vector<point> & p){
	int n = p.size();
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		ans += p[i].cross(p[(i+1)%n]);
	}
	return abs(ans);
}

bool isConvex(const vector<point> & p){
	int n = p.size();
	bool hasPos = false, hasNeg = false;
	for(int i = 0; i < n; ++i){
		point first = p[(i+1)%n] - p[i];
		point second = p[(i+2)%n] - p[(i+1)%n];
		lli sign = first.cross(second);
		if(sign > 0) hasPos = true;
		if(sign < 0) hasNeg = true;
	}
	return !(hasPos && hasNeg);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<point> points(n);
	for(int i = 0; i < n; ++i){
		cin >> points[i].x >> points[i].y;
	}
	sort(points.begin(), points.end());
	vector<int> mapeo(n);
	iota(mapeo.begin(), mapeo.end(), 0);
	vector<point> events;
	for(int i = 0; i < n-1; ++i){
		for(int j = i+1; j < n; ++j){
			point v = (points[i] - points[j]).perp();
			if(v.y < 0){
				v.x = -v.x;
				v.y = -v.y;
			}else if(v.y == 0){
				v.x = abs(v.x);
			}
			v.i = i, v.j = j;
			events.emplace_back(v);
		}
	}
	polarSort(events, point(0, 0), point(1, 0));
	lli total = 0;
	lli area_mini = -1, cnt_mini_convex = 0, cnt_mini_concave = 0;
	for(const point & v : events){
		int i = mapeo[v.i], j = mapeo[v.j];
		total += (lli)max(0, i) * (lli)max(0, n-1-j);
		for(int lhs = 1; lhs <= 2; ++lhs){
			int k = min(i, j)-lhs;
			if(k < 0 || k >= n) continue;
			for(int rhs = 1; rhs <= 2; ++rhs){
				int l = max(i, j)+rhs;
				if(l < 0 || l >= n) continue;
				//recta p[i] -> p[j]
				//recta p[k] -> p[l]
				lli area = getArea({points[i], points[k], points[j], points[l]});
				if(area == 0) continue;
				if(area_mini == -1 || area < area_mini){
					area_mini = area;
					bool is = isConvex({points[i], points[k], points[j], points[l]});
					cnt_mini_convex = is;
					cnt_mini_concave = !is;
				}else if(area == area_mini){
					bool is = isConvex({points[i], points[k], points[j], points[l]});
					cnt_mini_convex += is;
					cnt_mini_concave += !is;
				}
			}
		}
		if(v.y > 0){
			mapeo[v.i] = j;
			mapeo[v.j] = i;
			swap(points[i], points[j]);
		}
	}
	lli cnt_convex = total - (lli)n * (n-1) * (n-2) * (n-3) / 24;
	lli cnt_concave = total - 2*cnt_convex;
	cnt_mini_convex /= 2;
	cout << 4*cnt_mini_convex + 3*cnt_mini_concave + 2*(cnt_convex - cnt_mini_convex) + 1*(cnt_concave - cnt_mini_concave) << "\n";
	return 0;
}