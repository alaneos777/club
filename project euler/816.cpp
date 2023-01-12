#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

const ld inf = 1e18, eps = 1e-9;

ld geq(ld a, ld b){
	return a-b >= -eps;
}

ld le(ld a, ld b){
	return a-b < -eps;
}

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator-(const point& p) const{
		return point(x - p.x, y - p.y);
	}
	ld length() const{
		return sqrtl(x*x + y*y);
	}
	ld norm() const{
		return x*x + y*y;
	}
	bool operator<(const point& p) const{
		return x < p.x || (x == p.x && y < p.y);
	}
};

bool comp1(const point & a, const point & b){
	return a.y < b.y;
}
pair<point, point> closestPairOfPoints(vector<point> P){
	sort(P.begin(), P.end(), comp1);
	set<point> S;
	ld ans = inf;
	point p, q;
	int pos = 0;
	for(int i = 0; i < P.size(); ++i){
		while(pos < i && geq(P[i].y - P[pos].y, ans)){
			S.erase(P[pos++]);
		}
		auto lower = S.lower_bound({P[i].x - ans - eps, -inf}); // smallest j such that ans >= P[i].x - S[j].x
		auto upper = S.upper_bound({P[i].x + ans + eps, -inf}); // smallest j such that ans < S[j].x - P[i].x
		for(auto it = lower; it != upper; ++it){
			ld d = (P[i] - *it).length();
			if(le(d, ans)){
				ans = d;
				p = P[i];
				q = *it;
			}
		}
		S.insert(P[i]);
	}
	return {p, q};
}

int main(){
	int k = 2e6;
	vector<lli> s = {290797};
	while(s.size() < 2*k){
		s.push_back(s.back() * s.back() % 50515093);
	}
	vector<point> points(k);
	for(int i = 0; i < k; ++i){
		points[i] = point(s[2*i], s[2*i+1]);
	}
	auto ans = closestPairOfPoints(points);
	point p = ans.first, q = ans.second;
	cout << fixed << setprecision(9) << (p-q).length() << "\n";
	return 0;
}